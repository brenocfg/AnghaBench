#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ d_unit; TYPE_2__* d_dev; } ;
struct disk_devdesc {int /*<<< orphan*/  d_partition; int /*<<< orphan*/  d_slice; TYPE_1__ dd; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_4__ {char* dv_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PARTNONE ; 
 int /*<<< orphan*/  D_SLICENONE ; 
 int /*<<< orphan*/  altera_sdcard_get_mediasize () ; 
 int /*<<< orphan*/  altera_sdcard_get_sectorsize () ; 
 TYPE_2__ beri_sdcard_disk ; 
 int /*<<< orphan*/  disk_close (struct disk_devdesc*) ; 
 scalar_t__ disk_open (struct disk_devdesc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int disk_print (struct disk_devdesc*,char*,int) ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
beri_sdcard_disk_print(int verbose)
{
	struct disk_devdesc dev;
	char line[80];
	int ret;

	printf("%s devices:", beri_sdcard_disk.dv_name);
	if ((ret = pager_output("\n")) != 0)
		return (ret);
	
	snprintf(line, sizeof(line), "    sdcard%d   Altera SD card drive\n", 0);
	ret = pager_output(line);
	if (ret != 0)
	    return (ret);
	dev.dd.d_dev = &beri_sdcard_disk;
	dev.dd.d_unit = 0;
	dev.d_slice = D_SLICENONE;
	dev.d_partition = D_PARTNONE;
	if (disk_open(&dev, altera_sdcard_get_mediasize(),
	    altera_sdcard_get_sectorsize()) == 0) {
		snprintf(line, sizeof(line), "    sdcard%d", 0);
		ret = disk_print(&dev, line, verbose);
		disk_close(&dev);
	}
	return (ret);
}