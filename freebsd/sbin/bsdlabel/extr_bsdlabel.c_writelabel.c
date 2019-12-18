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
struct disklabel {int d_npartitions; int d_secsize; TYPE_1__* d_partitions; scalar_t__ d_checksum; void* d_magic2; void* d_magic; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_offset; scalar_t__ p_size; } ;

/* Variables and functions */
 void* DISKMAGIC ; 
 int /*<<< orphan*/  O_RDWR ; 
 scalar_t__ bbsize ; 
 scalar_t__ bootarea ; 
 int /*<<< orphan*/  bsd_disklabel_le_enc (scalar_t__,struct disklabel*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ disable_write ; 
 int /*<<< orphan*/  display (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dkcksum (struct disklabel*) ; 
 int errno ; 
 scalar_t__ geom_class_available (char*) ; 
 scalar_t__ installboot ; 
 scalar_t__ is_file ; 
 struct disklabel lab ; 
 scalar_t__ labeloffset ; 
 int labelsoffset ; 
 scalar_t__ lba_offset ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readboot () ; 
 int /*<<< orphan*/  specname ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnc (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 scalar_t__ write (int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
writelabel(void)
{
	int i, fd, serrno;
	struct disklabel *lp = &lab;

	if (disable_write) {
		warnx("write to disk label suppressed - label was as follows:");
		display(stdout, NULL);
		return (0);
	}

	lp->d_magic = DISKMAGIC;
	lp->d_magic2 = DISKMAGIC;
	lp->d_checksum = 0;
	lp->d_checksum = dkcksum(lp);
	if (installboot)
		readboot();
	for (i = 0; i < lab.d_npartitions; i++)
		if (lab.d_partitions[i].p_size)
			lab.d_partitions[i].p_offset += lba_offset;
	bsd_disklabel_le_enc(bootarea + labeloffset + labelsoffset * lab.d_secsize,
	    lp);

	fd = open(specname, O_RDWR);
	if (fd < 0) {
		if (is_file) {
			warn("cannot open file %s for writing label", specname);
			return(1);
		} else
			serrno = errno;

		if (geom_class_available("PART") != 0) {
			/*
			 * Since we weren't able open provider for
			 * writing, then recommend user to use gpart(8).
			 */
			warnc(serrno,
			    "cannot open provider %s for writing label",
			    specname);
			warnx("Try to use gpart(8).");
			return (1);
		}

		warnc(serrno, "%s", specname);
		return (1);
	} else {
		if (write(fd, bootarea, bbsize) != bbsize) {
			warn("write %s", specname);
			close (fd);
			return (1);
		}
		close (fd);
	}
	return (0);
}