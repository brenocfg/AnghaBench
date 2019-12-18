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
 int ENOENT ; 
 struct rcsection* rc_findsect (struct rcfile*,char const*) ; 
 struct rckey* rc_sect_findkey (struct rcsection*,char const*) ; 

int
rc_getstringptr(struct rcfile *rcp, const char *section, const char *key,
	char **dest)
{
	struct rcsection *rsp;
	struct rckey *rkp;
	
	*dest = NULL;
	rsp = rc_findsect(rcp, section);
	if (!rsp) return ENOENT;
	rkp = rc_sect_findkey(rsp,key);
	if (!rkp) return ENOENT;
	*dest = rkp->rk_value;
	return 0;
}