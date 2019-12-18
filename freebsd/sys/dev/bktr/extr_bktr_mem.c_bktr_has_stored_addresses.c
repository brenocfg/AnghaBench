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
struct TYPE_2__ {int addresses_stored; } ;

/* Variables and functions */
 int BKTR_MEM_MAX_DEVICES ; 
 TYPE_1__* memory_list ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int
bktr_has_stored_addresses(int unit)
{

	if (unit < 0 || unit >= BKTR_MEM_MAX_DEVICES) {
		printf("bktr_mem: Unit number %d invalid\n", unit);
		return 0;
	}

	return memory_list[unit].addresses_stored;
}