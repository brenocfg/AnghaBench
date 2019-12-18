#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* devclass_t ;
struct TYPE_3__ {scalar_t__* dev_list; } ;

/* Variables and functions */
 int DEVCLASS_MAXUNIT ; 

int
devclass_get_maxunit(devclass_t dc)
{
	int max_unit = 0;

	if (dc) {
		max_unit = DEVCLASS_MAXUNIT;
		while (max_unit--) {
			if (dc->dev_list[max_unit]) {
				break;
			}
		}
		max_unit++;
	}
	return (max_unit);
}