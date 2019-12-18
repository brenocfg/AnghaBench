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
struct rcsection {int dummy; } ;
struct rckey {char* rk_value; } ;
struct rcfile {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*,char const*) ; 
 scalar_t__ isspace (char) ; 
 struct rcsection* rc_findsect (struct rcfile*,char const*) ; 
 struct rckey* rc_sect_findkey (struct rcsection*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char*,char*) ; 

int
rc_getbool(struct rcfile *rcp, const char *section, const char *key, int *value)
{
	struct rcsection *rsp;
	struct rckey *rkp;
	char *p;
	
	rsp = rc_findsect(rcp, section);
	if (!rsp) return ENOENT;
	rkp = rc_sect_findkey(rsp,key);
	if (!rkp) return ENOENT;
	p = rkp->rk_value;
	while (*p && isspace(*p)) p++;
	if (*p == '0' || strcasecmp(p,"no") == 0 || strcasecmp(p,"false") == 0) {
		*value = 0;
		return 0;
	}
	if (*p == '1' || strcasecmp(p,"yes") == 0 || strcasecmp(p,"true") == 0) {
		*value = 1;
		return 0;
	}
	fprintf(stderr, "invalid boolean value '%s' for key '%s' in section '%s' \n",p, key, section);
	return EINVAL;
}