#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ub_ctx {int /*<<< orphan*/  cfglock; TYPE_2__* env; scalar_t__ finalized; } ;
typedef  int /*<<< orphan*/  ldata ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_1__* cfg; } ;
struct TYPE_3__ {int /*<<< orphan*/  local_data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int UB_AFTERFINAL ; 
 int UB_NOERROR ; 
 int UB_NOMEM ; 
 int UB_READFILE ; 
 int UB_SYNTAX ; 
 int /*<<< orphan*/  cfg_strlist_insert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 char* getenv (char*) ; 
 scalar_t__ isxdigit (unsigned char) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 scalar_t__ str_is_ip6 (char*) ; 
 char* strdup (char*) ; 

int
ub_ctx_hosts(struct ub_ctx* ctx, const char* fname)
{
	FILE* in;
	char buf[1024], ldata[1024];
	char* parse, *addr, *name, *ins;
	lock_basic_lock(&ctx->cfglock);
	if(ctx->finalized) {
		lock_basic_unlock(&ctx->cfglock);
		errno=EINVAL;
		return UB_AFTERFINAL;
	}
	lock_basic_unlock(&ctx->cfglock);
	if(fname == NULL) {
#if defined(UB_ON_WINDOWS) && defined(HAVE_WINDOWS_H)
		/*
		 * If this is Windows NT/XP/2K it's in
		 * %WINDIR%\system32\drivers\etc\hosts.
		 * If this is Windows 95/98/Me it's in %WINDIR%\hosts.
		 */
		name = getenv("WINDIR");
		if (name != NULL) {
			int retval=0;
			snprintf(buf, sizeof(buf), "%s%s", name, 
				"\\system32\\drivers\\etc\\hosts");
			if((retval=ub_ctx_hosts(ctx, buf)) !=0 ) {
				snprintf(buf, sizeof(buf), "%s%s", name, 
					"\\hosts");
				retval=ub_ctx_hosts(ctx, buf);
			}
			return retval;
		}
		return UB_READFILE;
#else
		fname = "/etc/hosts";
#endif /* WIN32 */
	}
	in = fopen(fname, "r");
	if(!in) {
		/* error in errno! perror(fname) */
		return UB_READFILE;
	}
	while(fgets(buf, (int)sizeof(buf), in)) {
		buf[sizeof(buf)-1] = 0;
		parse=buf;
		while(*parse == ' ' || *parse == '\t')
			parse++;
		if(*parse == '#')
			continue; /* skip comment */
		/* format: <addr> spaces <name> spaces <name> ... */
		addr = parse;
		/* skip addr */
		while(isxdigit((unsigned char)*parse) || *parse == '.' || *parse == ':')
			parse++;
		if(*parse == '\r')
			parse++;
		if(*parse == '\n' || *parse == 0)
			continue;
		if(*parse == '%') 
			continue; /* ignore macOSX fe80::1%lo0 localhost */
		if(*parse != ' ' && *parse != '\t') {
			/* must have whitespace after address */
			fclose(in);
			errno=EINVAL;
			return UB_SYNTAX;
		}
		*parse++ = 0; /* end delimiter for addr ... */
		/* go to names and add them */
		while(*parse) {
			while(*parse == ' ' || *parse == '\t' || *parse=='\n'
				|| *parse=='\r')
				parse++;
			if(*parse == 0 || *parse == '#')
				break;
			/* skip name, allows (too) many printable characters */
			name = parse;
			while('!' <= *parse && *parse <= '~')
				parse++;
			if(*parse)
				*parse++ = 0; /* end delimiter for name */
			snprintf(ldata, sizeof(ldata), "%s %s %s",
				name, str_is_ip6(addr)?"AAAA":"A", addr);
			ins = strdup(ldata);
			if(!ins) {
				/* out of memory */
				fclose(in);
				errno=ENOMEM;
				return UB_NOMEM;
			}
			lock_basic_lock(&ctx->cfglock);
			if(!cfg_strlist_insert(&ctx->env->cfg->local_data, 
				ins)) {
				lock_basic_unlock(&ctx->cfglock);
				fclose(in);
				errno=ENOMEM;
				return UB_NOMEM;
			}
			lock_basic_unlock(&ctx->cfglock);
		}
	}
	fclose(in);
	return UB_NOERROR;
}