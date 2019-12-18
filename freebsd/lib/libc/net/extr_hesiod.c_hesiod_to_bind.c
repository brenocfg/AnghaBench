#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hesiod_p {char* rhs; char const* lhs; } ;
typedef  int /*<<< orphan*/  bindname ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAXDNAME ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  hesiod_free_list (void*,char**) ; 
 char** hesiod_resolve (void*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *
hesiod_to_bind(void *context, const char *name, const char *type)
{
	struct hesiod_p *ctx = (struct hesiod_p *) context;
	char		 bindname[MAXDNAME], *p, *ret, **rhs_list = NULL;
	const char	*rhs;
	int		 len;

	if (strlcpy(bindname, name, sizeof(bindname)) >= sizeof(bindname)) {
		errno = EMSGSIZE;
		return NULL;
	}

		/*
		 * Find the right right hand side to use, possibly
		 * truncating bindname.
		 */
	p = strchr(bindname, '@');
	if (p) {
		*p++ = 0;
		if (strchr(p, '.'))
			rhs = name + (p - bindname);
		else {
			rhs_list = hesiod_resolve(context, p, "rhs-extension");
			if (rhs_list)
				rhs = *rhs_list;
			else {
				errno = ENOENT;
				return NULL;
			}
		}
	} else
		rhs = ctx->rhs;

		/* See if we have enough room. */
	len = strlen(bindname) + 1 + strlen(type);
	if (ctx->lhs)
		len += strlen(ctx->lhs) + ((ctx->lhs[0] != '.') ? 1 : 0);
	len += strlen(rhs) + ((rhs[0] != '.') ? 1 : 0);
	if (len > sizeof(bindname) - 1) {
		if (rhs_list)
			hesiod_free_list(context, rhs_list);
		errno = EMSGSIZE;
		return NULL;
	}
		/* Put together the rest of the domain. */
	strcat(bindname, ".");
	strcat(bindname, type);
		/* Only append lhs if it isn't empty. */
	if (ctx->lhs && ctx->lhs[0] != '\0' ) {
		if (ctx->lhs[0] != '.')
			strcat(bindname, ".");
		strcat(bindname, ctx->lhs);
	}
	if (rhs[0] != '.')
		strcat(bindname, ".");
	strcat(bindname, rhs);

		/* rhs_list is no longer needed, since we're done with rhs. */
	if (rhs_list)
		hesiod_free_list(context, rhs_list);

		/* Make a copy of the result and return it to the caller. */
	ret = strdup(bindname);
	if (!ret)
		errno = ENOMEM;
	return ret;
}