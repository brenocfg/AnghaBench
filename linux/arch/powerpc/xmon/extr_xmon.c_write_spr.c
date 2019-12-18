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
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_spr_faults ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 scalar_t__ xmon_is_ro ; 
 int /*<<< orphan*/  xmon_mtspr (int,unsigned long) ; 
 char* xmon_ro_msg ; 

__attribute__((used)) static void
write_spr(int n, unsigned long val)
{
	if (xmon_is_ro) {
		printf(xmon_ro_msg);
		return;
	}

	if (setjmp(bus_error_jmp) == 0) {
		catch_spr_faults = 1;
		sync();

		xmon_mtspr(n, val);

		sync();
	} else {
		printf("SPR 0x%03x (%4d) Faulted during write\n", n, n);
	}
	catch_spr_faults = 0;
}