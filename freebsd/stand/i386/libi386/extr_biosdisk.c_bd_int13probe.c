#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {int bd_flags; int bd_unit; scalar_t__ bd_sectors; int bd_cyl; int bd_hds; int bd_sec; int /*<<< orphan*/  bd_sectorsize; } ;
typedef  TYPE_1__ bdinfo_t ;
struct TYPE_13__ {char* dv_name; } ;
struct TYPE_12__ {char* dv_name; } ;
struct TYPE_11__ {char* dv_name; } ;
struct TYPE_10__ {int addr; int eax; int edx; int /*<<< orphan*/  efl; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int BD_CDROM ; 
 int BD_FLOPPY ; 
 int BD_MODEEDD1 ; 
 int BD_MODEEDD3 ; 
 int BD_MODEINT13 ; 
 int BD_NO_MEDIA ; 
 int /*<<< orphan*/  BIOSDISK_SECSIZE ; 
 int /*<<< orphan*/  DPRINTF (char*,int,int,int,int) ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 int bd_check_extensions (int) ; 
 int bd_get_diskinfo_ext (TYPE_1__*) ; 
 int bd_get_diskinfo_std (TYPE_1__*) ; 
 int /*<<< orphan*/  bd_reset_disk (int) ; 
 TYPE_5__ bioscd ; 
 TYPE_4__ biosfd ; 
 TYPE_3__ bioshd ; 
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 TYPE_2__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static bool
bd_int13probe(bdinfo_t *bd)
{
	int edd, ret;

	bd->bd_flags &= ~BD_NO_MEDIA;

	edd = bd_check_extensions(bd->bd_unit);
	if (edd == 0)
		bd->bd_flags |= BD_MODEINT13;
	else if (edd < 0x30)
		bd->bd_flags |= BD_MODEEDD1;
	else
		bd->bd_flags |= BD_MODEEDD3;

	/* Default sector size */
	bd->bd_sectorsize = BIOSDISK_SECSIZE;

	/*
	 * Test if the floppy device is present, so we can avoid receiving
	 * bogus information from bd_get_diskinfo_std().
	 */
	if (bd->bd_unit < 0x80) {
		/* reset disk */
		bd_reset_disk(bd->bd_unit);

		/* Get disk type */
		v86.ctl = V86_FLAGS;
		v86.addr = 0x13;
		v86.eax = 0x1500;
		v86.edx = bd->bd_unit;
		v86int();
		if (V86_CY(v86.efl) || (v86.eax & 0x300) == 0)
			return (false);
	}

	ret = 1;
	if (edd != 0)
		ret = bd_get_diskinfo_ext(bd);
	if (ret != 0 || bd->bd_sectors == 0)
		ret = bd_get_diskinfo_std(bd);

	if (ret != 0 && bd->bd_unit < 0x80) {
		/* Set defaults for 1.44 floppy */
		bd->bd_cyl = 80;
		bd->bd_hds = 2;
		bd->bd_sec = 18;
		bd->bd_sectors = 2880;
		/* Since we are there, there most likely is no media */
		bd->bd_flags |= BD_NO_MEDIA;
		ret = 0;
	}

	if (ret != 0) {
		/* CD is special case, bc_add() has its own fallback. */
		if ((bd->bd_flags & BD_CDROM) != 0)
			return (true);

		if (bd->bd_sectors != 0 && edd != 0) {
			bd->bd_sec = 63;
			bd->bd_hds = 255;
			bd->bd_cyl =
			    (bd->bd_sectors + bd->bd_sec * bd->bd_hds - 1) /
			    bd->bd_sec * bd->bd_hds;
		} else {
			const char *dv_name;

			if ((bd->bd_flags & BD_FLOPPY) != 0)
				dv_name = biosfd.dv_name;
			else if ((bd->bd_flags & BD_CDROM) != 0)
				dv_name = bioscd.dv_name;
			else
				dv_name = bioshd.dv_name;

			printf("Can not get information about %s unit %#x\n",
			    dv_name, bd->bd_unit);
			return (false);
		}
	}

	if (bd->bd_sec == 0)
		bd->bd_sec = 63;
	if (bd->bd_hds == 0)
		bd->bd_hds = 255;

	if (bd->bd_sectors == 0)
		bd->bd_sectors = (uint64_t)bd->bd_cyl * bd->bd_hds * bd->bd_sec;

	DPRINTF("unit 0x%x geometry %d/%d/%d\n", bd->bd_unit, bd->bd_cyl,
	    bd->bd_hds, bd->bd_sec);

	return (true);
}