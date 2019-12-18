#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mask; } ;

/* Variables and functions */
 TYPE_1__* cheetah_error_table ; 

__attribute__((used)) static inline unsigned long cheetah_get_hipri(unsigned long afsr)
{
	unsigned long tmp = 0;
	int i;

	for (i = 0; cheetah_error_table[i].mask; i++) {
		if ((tmp = (afsr & cheetah_error_table[i].mask)) != 0UL)
			return tmp;
	}
	return tmp;
}