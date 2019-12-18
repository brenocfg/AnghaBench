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
 scalar_t__ BVM_DBG_SIG ; 
 int bvm_dbg_port ; 
 scalar_t__ inw (int) ; 
 scalar_t__ resource_int_value (char*,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static int
bvm_dbg_probe(void)
{
	int disabled, port;

	disabled = 0;
	resource_int_value("bvmdbg", 0, "disabled", &disabled);

	if (!disabled) {
		if (resource_int_value("bvmdbg", 0, "port", &port) == 0)
			bvm_dbg_port = port;

		if (inw(bvm_dbg_port) == BVM_DBG_SIG) {
			/*
			 * Return a higher priority than 0 to override other
			 * gdb dbgport providers that may be present (e.g. uart)
			 */
			return (1);
		}
	}

	return (-1);
}