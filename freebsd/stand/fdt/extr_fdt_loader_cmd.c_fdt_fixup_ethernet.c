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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdt_path_offset (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fdt_setprop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  fdt_strtovectx (char const*,int /*<<< orphan*/ **,int,int) ; 
 int /*<<< orphan*/  fdtp ; 

void
fdt_fixup_ethernet(const char *str, char *ethstr, int len)
{
	uint8_t tmp_addr[6];

	/* Convert macaddr string into a vector of uints */
	fdt_strtovectx(str, &tmp_addr, 6, sizeof(uint8_t));
	/* Set actual property to a value from vect */
	fdt_setprop(fdtp, fdt_path_offset(fdtp, ethstr),
	    "local-mac-address", &tmp_addr, 6 * sizeof(uint8_t));
}