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
idt2date(date *dt, date *idt)
{

	dt->d = idt->d + 1;
	if (idt->m < 10) {
		dt->m = idt->m + 3;
		dt->y = idt->y;
	} else {
		dt->m = idt->m - 9;
		dt->y = idt->y + 1;
	}
	if (dt->m < 1)
		return (NULL);
	else
		return (dt);
}