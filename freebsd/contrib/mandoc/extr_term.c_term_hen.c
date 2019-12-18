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
struct termp {int (* hspan ) (struct termp const*,struct roffsu const*) ;} ;
struct roffsu {int dummy; } ;

/* Variables and functions */
 int stub1 (struct termp const*,struct roffsu const*) ; 

int
term_hen(const struct termp *p, const struct roffsu *su)
{
	int bu;

	if ((bu = (*p->hspan)(p, su)) >= 0)
		return (bu + 11) / 24;
	else
		return -((-bu + 11) / 24);
}