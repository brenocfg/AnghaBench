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
struct bgx {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int bgx_fdt_init_phy (struct bgx*) ; 

__attribute__((used)) static int
bgx_init_phy(struct bgx *bgx)
{
	int err;

	/* By default we fail */
	err = ENXIO;
#ifdef FDT
	err = bgx_fdt_init_phy(bgx);
#endif
#ifdef ACPI
	if (err != 0) {
		/* ARM64TODO: Add ACPI function here */
	}
#endif
	return (err);
}