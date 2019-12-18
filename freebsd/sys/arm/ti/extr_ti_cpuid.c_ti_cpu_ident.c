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

/* Variables and functions */
#define  CHIP_AM335X 129 
#define  CHIP_OMAP_4 128 
 int /*<<< orphan*/  am335x_get_revision () ; 
 int /*<<< orphan*/  omap4_get_revision () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int ti_chip () ; 
 int /*<<< orphan*/  ti_soc_is_supported () ; 

__attribute__((used)) static void
ti_cpu_ident(void *dummy)
{
	if (!ti_soc_is_supported())
		return;
	switch(ti_chip()) {
	case CHIP_OMAP_4:
		omap4_get_revision();
		break;
	case CHIP_AM335X:
		am335x_get_revision();
		break;
	default:
		panic("Unknown chip type, fixme!\n");
	}
}