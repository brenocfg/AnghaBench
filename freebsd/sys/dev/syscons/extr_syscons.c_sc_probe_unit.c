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
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 char* SC_DRIVER_NAME ; 
 int /*<<< orphan*/  VTY_SC ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  sckbdprobe (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scvidprobe (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vty_enabled (int /*<<< orphan*/ ) ; 

int
sc_probe_unit(int unit, int flags)
{
    if (!vty_enabled(VTY_SC))
        return ENXIO;
    if (!scvidprobe(unit, flags, FALSE)) {
	if (bootverbose)
	    printf("%s%d: no video adapter found.\n", SC_DRIVER_NAME, unit);
	return ENXIO;
    }

    /* syscons will be attached even when there is no keyboard */
    sckbdprobe(unit, flags, FALSE);

    return 0;
}