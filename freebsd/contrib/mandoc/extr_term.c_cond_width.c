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
struct termp {size_t (* width ) (struct termp const*,int) ;} ;

/* Variables and functions */
 size_t stub1 (struct termp const*,int) ; 

__attribute__((used)) static size_t
cond_width(const struct termp *p, int c, int *skip)
{

	if (*skip) {
		(*skip) = 0;
		return 0;
	} else
		return (*p->width)(p, c);
}