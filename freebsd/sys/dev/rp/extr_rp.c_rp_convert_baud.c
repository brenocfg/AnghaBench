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
struct TYPE_2__ {int baud; int conversion; } ;

/* Variables and functions */
 TYPE_1__* baud_table ; 

__attribute__((used)) static int rp_convert_baud(int baud) {
	int i;

	for (i = 0; baud_table[i].baud >= 0; i++) {
		if (baud_table[i].baud == baud)
			break;
	}

	return baud_table[i].conversion;
}