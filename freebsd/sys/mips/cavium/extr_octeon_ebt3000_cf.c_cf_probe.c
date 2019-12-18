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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 int BUS_PROBE_NOWILDCARD ; 
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int ENXIO ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 scalar_t__ device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int cf_probe (device_t dev)
{
    	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
		return (ENXIO);

	if (device_get_unit(dev) != 0) {
                panic("can't attach more devices\n");
        }

        device_set_desc(dev, "Octeon Compact Flash Driver");

	return (BUS_PROBE_NOWILDCARD);
}