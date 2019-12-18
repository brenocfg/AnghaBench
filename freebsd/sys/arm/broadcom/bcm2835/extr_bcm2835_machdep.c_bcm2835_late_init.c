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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  platform_t ;
typedef  int phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  cells ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int OF_getencprop (int,char*,int*,int) ; 
 int /*<<< orphan*/  board_set_revision (int) ; 
 int /*<<< orphan*/  board_set_serial (int) ; 

__attribute__((used)) static void
bcm2835_late_init(platform_t plat)
{
	phandle_t system;
	pcell_t cells[2];
	int len;

	system = OF_finddevice("/system");
	if (system != -1) {
		len = OF_getencprop(system, "linux,serial", cells,
		    sizeof(cells));
		if (len > 0)
			board_set_serial(((uint64_t)cells[0]) << 32 | cells[1]);

		len = OF_getencprop(system, "linux,revision", cells,
		    sizeof(cells));
		if (len > 0)
			board_set_revision(cells[0]);
	}
}