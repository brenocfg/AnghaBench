#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int pages_size; scalar_t__ pages_number; } ;
struct TYPE_4__ {int id; scalar_t__ logical_address; TYPE_1__ Device; } ;

/* Variables and functions */
#define  AT45DB128 131 
#define  AT45DB161 130 
#define  AT45DB321 129 
#define  AT45DB642 128 
 int CFG_MAX_DATAFLASH_BANKS ; 
 TYPE_2__* dataflash_info ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void AT91F_DataflashPrintInfo(void)
{
	int i;
	for (i = 0; i < CFG_MAX_DATAFLASH_BANKS; i++) {
		if (dataflash_info[i].id != 0) {
			printf ("DF:AT45DB");
			switch (dataflash_info[i].id) {
			case AT45DB161:
				printf ("161");
				break;

			case AT45DB321:
				printf ("321");
				break;

			case AT45DB642:
				printf ("642");
				break;
			case AT45DB128:				
				printf ("128");
				break;
			}

			printf ("\n# PG: %6d\n"
				"PG SZ: %6d\n"
				"SZ=%8d bytes\n"
				"ADDR: %08X\n",
				(unsigned int) dataflash_info[i].Device.pages_number,
				(unsigned int) dataflash_info[i].Device.pages_size,
				(unsigned int) dataflash_info[i].Device.pages_number *
				dataflash_info[i].Device.pages_size,
				(unsigned int) dataflash_info[i].logical_address);
		}
	}
}