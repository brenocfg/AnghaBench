#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t* autodetect; } ;
struct TYPE_5__ {int probed_format; } ;
struct TYPE_4__ {scalar_t__ sect; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 TYPE_2__* DRS ; 
 TYPE_1__* floppy_type ; 

__attribute__((used)) static int next_valid_format(void)
{
	int probed_format;

	probed_format = DRS->probed_format;
	while (1) {
		if (probed_format >= 8 || !DP->autodetect[probed_format]) {
			DRS->probed_format = 0;
			return 1;
		}
		if (floppy_type[DP->autodetect[probed_format]].sect) {
			DRS->probed_format = probed_format;
			return 0;
		}
		probed_format++;
	}
}