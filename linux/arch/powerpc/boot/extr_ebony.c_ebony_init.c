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
struct TYPE_2__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dtb_start ; 
 int /*<<< orphan*/  ebony_fixups ; 
 void* ebony_mac0 ; 
 void* ebony_mac1 ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibm44x_dbcr_reset ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  serial_console_init () ; 

void ebony_init(void *mac0, void *mac1)
{
	platform_ops.fixups = ebony_fixups;
	platform_ops.exit = ibm44x_dbcr_reset;
	ebony_mac0 = mac0;
	ebony_mac1 = mac1;
	fdt_init(_dtb_start);
	serial_console_init();
}