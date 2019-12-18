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
typedef  int uint32_t ;
struct sun_disklabel {int sl_rpm; int sl_pcylinders; int sl_interleave; int sl_ncylinders; int sl_acylinders; int sl_nsectors; int sl_ntracks; int /*<<< orphan*/  sl_text; TYPE_1__* sl_part; scalar_t__ sl_sparespercyl; } ;
typedef  int /*<<< orphan*/  path ;
typedef  long off_t ;
typedef  int intmax_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int sdkp_nsectors; scalar_t__ sdkp_cyloffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGFWHEADS ; 
 int /*<<< orphan*/  DIOCGFWSECTORS ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 size_t SUN_RAWPART ; 
 int SUN_SIZE ; 
 char* _PATH_DEV ; 
 int /*<<< orphan*/  bzero (struct sun_disklabel*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int mediasize ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int sectorsize ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int sunlabel_dec (char*,struct sun_disklabel*) ; 

__attribute__((used)) static void
read_label(struct sun_disklabel *sl, const char *disk)
{
	char path[MAXPATHLEN];
	uint32_t fwsectors;
	uint32_t fwheads;
	char buf[SUN_SIZE];
	int fd, error;

	snprintf(path, sizeof(path), "%s%s", _PATH_DEV, disk);
	if ((fd = open(path, O_RDONLY)) < 0)
		err(1, "open %s", path);
	if (read(fd, buf, sizeof(buf)) != sizeof(buf))
		err(1, "read");
	error = sunlabel_dec(buf, sl);
	if (ioctl(fd, DIOCGMEDIASIZE, &mediasize) != 0)
		if (error)
			err(1, "%s: ioctl(DIOCGMEDIASIZE) failed", disk);
	if (ioctl(fd, DIOCGSECTORSIZE, &sectorsize) != 0) {
		if (error)
			err(1, "%s: DIOCGSECTORSIZE failed", disk);
		else
			sectorsize = 512;
	}
	if (error) {
		bzero(sl, sizeof(*sl));
		if (ioctl(fd, DIOCGFWSECTORS, &fwsectors) != 0)
			fwsectors = 63;
		if (ioctl(fd, DIOCGFWHEADS, &fwheads) != 0) {
			if (mediasize <= 63 * 1024 * sectorsize)
				fwheads = 1;
			else if (mediasize <= 63 * 16 * 1024 * sectorsize)
				fwheads = 16;
			else
				fwheads = 255;
		}
		sl->sl_rpm = 3600;
		sl->sl_pcylinders = mediasize / (fwsectors * fwheads *
		    sectorsize);
		sl->sl_sparespercyl = 0;
		sl->sl_interleave = 1;
		sl->sl_ncylinders = sl->sl_pcylinders - 2;
		sl->sl_acylinders = 2;
		sl->sl_nsectors = fwsectors;
		sl->sl_ntracks = fwheads;
		sl->sl_part[SUN_RAWPART].sdkp_cyloffset = 0;
		sl->sl_part[SUN_RAWPART].sdkp_nsectors = sl->sl_ncylinders *
		    sl->sl_ntracks * sl->sl_nsectors;
		if (mediasize > (off_t)4999L * 1024L * 1024L) {
			sprintf(sl->sl_text,
			    "FreeBSD%jdG cyl %u alt %u hd %u sec %u",
			    (intmax_t)(mediasize + 512 * 1024 * 1024) /
			        (1024 * 1024 * 1024),
			    sl->sl_ncylinders, sl->sl_acylinders,
			    sl->sl_ntracks, sl->sl_nsectors);
		} else {
			sprintf(sl->sl_text,
			    "FreeBSD%jdM cyl %u alt %u hd %u sec %u",
			    (intmax_t)(mediasize + 512 * 1024) / (1024 * 1024),
			    sl->sl_ncylinders, sl->sl_acylinders,
			    sl->sl_ntracks, sl->sl_nsectors);
		}
	}
	close(fd);
}