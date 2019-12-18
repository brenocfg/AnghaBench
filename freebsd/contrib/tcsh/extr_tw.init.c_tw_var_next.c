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
struct Strbuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ tw_env ; 
 int tw_envvar_next (struct Strbuf*,struct Strbuf*,int*) ; 
 int tw_shvar_next (struct Strbuf*,struct Strbuf*,int*) ; 
 scalar_t__ tw_vptr ; 

int
tw_var_next(struct Strbuf *res, struct Strbuf *dir, int *flags)
{
    int ret = 0;

    if (tw_vptr)
	ret = tw_shvar_next(res, dir, flags);
    if (ret == 0 && tw_env)
	ret = tw_envvar_next(res, dir, flags);
    return ret;
}