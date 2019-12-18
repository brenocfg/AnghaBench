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

/* Variables and functions */
 scalar_t__ MV_DUMP_WIN ; 
 scalar_t__ MV_SOC_ARMADA_XP ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  decode_win_cpu_setup () ; 
 int decode_win_sdram_fixup () ; 
 scalar_t__ eth_port ; 
 int fdt_win_setup () ; 
 int /*<<< orphan*/  pm_disable_device (int) ; 
 int /*<<< orphan*/  soc_dump_decode_win () ; 
 scalar_t__ soc_family ; 
 int /*<<< orphan*/  soc_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_port ; 
 int win_cpu_from_dt () ; 

int
soc_decode_win(void)
{
	uint32_t dev, rev;
	int mask, err;

	mask = 0;
	TUNABLE_INT_FETCH("hw.pm-disable-mask", &mask);

	if (mask != 0)
		pm_disable_device(mask);

	/* Retrieve data about physical addresses from device tree. */
	if ((err = win_cpu_from_dt()) != 0)
		return (err);

	/* Retrieve our ID: some windows facilities vary between SoC models */
	soc_id(&dev, &rev);

	if (soc_family == MV_SOC_ARMADA_XP)
		if ((err = decode_win_sdram_fixup()) != 0)
			return(err);


	decode_win_cpu_setup();
	if (MV_DUMP_WIN)
		soc_dump_decode_win();

	eth_port = 0;
	usb_port = 0;
	if ((err = fdt_win_setup()) != 0)
		return (err);

	return (0);
}