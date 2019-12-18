#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ub_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int ULONG ;
struct TYPE_6__ {char* String; } ;
struct TYPE_7__ {struct TYPE_7__* Next; TYPE_1__ IpAddress; } ;
struct TYPE_8__ {TYPE_2__ DnsServerList; } ;
typedef  TYPE_2__ IP_ADDR_STRING ;
typedef  TYPE_3__ FIXED_INFO ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ERROR_BUFFER_OVERFLOW ; 
 scalar_t__ GetNetworkParams (TYPE_3__*,int*) ; 
 scalar_t__ NO_ERROR ; 
 int UB_NOERROR ; 
 int UB_READFILE ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ isxdigit (unsigned char) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int ub_ctx_set_fwd (struct ub_ctx*,char*) ; 

int 
ub_ctx_resolvconf(struct ub_ctx* ctx, const char* fname)
{
	FILE* in;
	int numserv = 0;
	char buf[1024];
	char* parse, *addr;
	int r;

	if(fname == NULL) {
#if !defined(UB_ON_WINDOWS) || !defined(HAVE_WINDOWS_H)
		fname = "/etc/resolv.conf";
#else
		FIXED_INFO *info;
		ULONG buflen = sizeof(*info);
		IP_ADDR_STRING *ptr;

		info = (FIXED_INFO *) malloc(sizeof (FIXED_INFO));
		if (info == NULL) 
			return UB_READFILE;

		if (GetNetworkParams(info, &buflen) == ERROR_BUFFER_OVERFLOW) {
			free(info);
			info = (FIXED_INFO *) malloc(buflen);
			if (info == NULL)
				return UB_READFILE;
		}

		if (GetNetworkParams(info, &buflen) == NO_ERROR) {
			int retval=0;
			ptr = &(info->DnsServerList);
			while (ptr) {
				numserv++;
				if((retval=ub_ctx_set_fwd(ctx, 
					ptr->IpAddress.String))!=0) {
					free(info);
					return retval;
				}
				ptr = ptr->Next;
			}
			free(info);
			if (numserv==0)
				return UB_READFILE;
			return UB_NOERROR;
		}
		free(info);
		return UB_READFILE;
#endif /* WINDOWS */
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
		if(strncmp(parse, "nameserver", 10) == 0) {
			numserv++;
			parse += 10; /* skip 'nameserver' */
			/* skip whitespace */
			while(*parse == ' ' || *parse == '\t')
				parse++;
			addr = parse;
			/* skip [0-9a-fA-F.:]*, i.e. IP4 and IP6 address */
			while(isxdigit((unsigned char)*parse) || *parse=='.' || *parse==':')
				parse++;
			/* terminate after the address, remove newline */
			*parse = 0;
			
			if((r = ub_ctx_set_fwd(ctx, addr)) != UB_NOERROR) {
				fclose(in);
				return r;
			}
		}
	}
	fclose(in);
	if(numserv == 0) {
		/* from resolv.conf(5) if none given, use localhost */
		return ub_ctx_set_fwd(ctx, "127.0.0.1");
	}
	return UB_NOERROR;
}