#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int bd_unit; scalar_t__ bd_sectors; int /*<<< orphan*/  bd_flags; int /*<<< orphan*/  bd_sectorsize; } ;
typedef  TYPE_1__ bdinfo_t ;
struct TYPE_8__ {char* dv_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_FLOPPY ; 
 int /*<<< orphan*/  BD_NO_MEDIA ; 
 int /*<<< orphan*/  BIOSDISK_SECSIZE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_add_dev (int) ; 
 scalar_t__ bd_get_diskinfo_std (TYPE_1__*) ; 
 int /*<<< orphan*/  bd_link ; 
 TYPE_4__ biosfd ; 
 TYPE_1__* calloc (int,int) ; 
 int fd_count () ; 
 int /*<<< orphan*/  fdinfo ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char,char*,int) ; 

__attribute__((used)) static int
fd_init(void)
{
	int unit, numfd;
	bdinfo_t *bd;

	numfd = fd_count();
	for (unit = 0; unit < numfd; unit++) {
		if ((bd = calloc(1, sizeof(*bd))) == NULL)
			break;

		bd->bd_sectorsize = BIOSDISK_SECSIZE;
		bd->bd_flags = BD_FLOPPY;
		bd->bd_unit = unit;

		/* Use std diskinfo for floppy drive */
		if (bd_get_diskinfo_std(bd) != 0) {
			free(bd);
			break;
		}
		if (bd->bd_sectors == 0)
			bd->bd_flags |= BD_NO_MEDIA;

		printf("BIOS drive %c: is %s%d\n", ('A' + unit),
		    biosfd.dv_name, unit);

		STAILQ_INSERT_TAIL(&fdinfo, bd, bd_link);
	}

	bcache_add_dev(unit);
	return (0);
}