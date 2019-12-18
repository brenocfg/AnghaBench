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
typedef  int uint8_t ;
typedef  int UINTN ;

/* Variables and functions */
 int CMD_OK ; 
 int CMD_WARN ; 
 scalar_t__ pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
efi_print_other_value(uint8_t *data, UINTN datasz)
{
	UINTN i;
	bool is_ascii = true;

	printf(" = ");
	for (i = 0; i < datasz - 1; i++) {
		/*
		 * Quick hack to see if this ascii-ish string is printable
		 * range plus tab, cr and lf.
		 */
		if ((data[i] < 32 || data[i] > 126)
		    && data[i] != 9 && data[i] != 10 && data[i] != 13) {
			is_ascii = false;
			break;
		}
	}
	if (data[datasz - 1] != '\0')
		is_ascii = false;
	if (is_ascii == true) {
		printf("%s", data);
		if (pager_output("\n"))
			return (CMD_WARN);
	} else {
		if (pager_output("\n"))
			return (CMD_WARN);
		/*
		 * Dump hex bytes grouped by 4.
		 */
		for (i = 0; i < datasz; i++) {
			printf("%02x ", data[i]);
			if ((i + 1) % 4 == 0)
				printf(" ");
			if ((i + 1) % 20 == 0) {
				if (pager_output("\n"))
					return (CMD_WARN);
			}
		}
		if (pager_output("\n"))
			return (CMD_WARN);
	}

	return (CMD_OK);
}