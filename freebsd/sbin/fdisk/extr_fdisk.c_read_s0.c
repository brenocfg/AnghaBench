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
struct TYPE_2__ {int /*<<< orphan*/ * parts; int /*<<< orphan*/ * bootinst; int /*<<< orphan*/  bootinst_size; } ;

/* Variables and functions */
 scalar_t__ DOSMAGIC ; 
 size_t DOSMAGICOFFSET ; 
 int DOSPARTOFF ; 
 int DOSPARTSIZE ; 
 int NDOSPART ; 
 int /*<<< orphan*/  dos_partition_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ le16dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 
 TYPE_1__ mboot ; 
 int read_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  secsize ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
read_s0()
{
	int i;

	mboot.bootinst_size = secsize;
	if (mboot.bootinst != NULL)
		free(mboot.bootinst);
	if ((mboot.bootinst = malloc(mboot.bootinst_size)) == NULL) {
		warnx("unable to allocate buffer to read fdisk "
		      "partition table");
		return -1;
	}
	if (read_disk(0, mboot.bootinst) == -1) {
		warnx("can't read fdisk partition table");
		return -1;
	}
	if (le16dec(&mboot.bootinst[DOSMAGICOFFSET]) != DOSMAGIC) {
		warnx("invalid fdisk partition table found");
		/* So should we initialize things */
		return -1;
	}
	for (i = 0; i < NDOSPART; i++)
		dos_partition_dec(
		    &mboot.bootinst[DOSPARTOFF + i * DOSPARTSIZE],
		    &mboot.parts[i]);
	return 0;
}