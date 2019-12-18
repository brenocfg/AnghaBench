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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CBBR_MEMBASE0 ; 
 int CBBR_MEMLIMIT0 ; 
 int /*<<< orphan*/  DEVPRINTF (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  cbb_activate_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cbb_cardbus_mem_open(device_t brdev, int win, uint32_t start, uint32_t end)
{
	int basereg;
	int limitreg;

	if ((win < 0) || (win > 1)) {
		DEVPRINTF((brdev,
		    "cbb_cardbus_mem_open: window out of range %d\n", win));
		return (EINVAL);
	}

	basereg = win * 8 + CBBR_MEMBASE0;
	limitreg = win * 8 + CBBR_MEMLIMIT0;

	pci_write_config(brdev, basereg, start, 4);
	pci_write_config(brdev, limitreg, end, 4);
	cbb_activate_window(brdev, SYS_RES_MEMORY);
	return (0);
}