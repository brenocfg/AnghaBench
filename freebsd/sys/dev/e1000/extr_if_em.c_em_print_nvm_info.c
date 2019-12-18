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
typedef  int u16 ;
struct adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_read_nvm (int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
em_print_nvm_info(struct adapter *adapter)
{
	u16 eeprom_data;
	int i, j, row = 0;

	/* Its a bit crude, but it gets the job done */
	printf("\nInterface EEPROM Dump:\n");
	printf("Offset\n0x0000  ");
	for (i = 0, j = 0; i < 32; i++, j++) {
		if (j == 8) { /* Make the offset block */
			j = 0; ++row;
			printf("\n0x00%x0  ",row);
		}
		e1000_read_nvm(&adapter->hw, i, 1, &eeprom_data);
		printf("%04x ", eeprom_data);
	}
	printf("\n");
}