#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int m; scalar_t__ y; scalar_t__ d; } ;
typedef  TYPE_1__ date ;

/* Variables and functions */

__attribute__((used)) static date *
date2idt(date *idt, date *dt)
{

	idt->d = dt->d - 1;
	if (dt->m > 2) {
		idt->m = dt->m - 3;
		idt->y = dt->y;
	} else {
		idt->m = dt->m + 9;
		idt->y = dt->y - 1;
	}
	if (idt->m < 0 || idt->m > 11 || idt->y < 0)
		return (NULL);
	else
		return idt;
}