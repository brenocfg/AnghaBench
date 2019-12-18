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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* getprogname () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr,
	    "usage: %s [ -fsoptions ] special-device%s\n",
	    getprogname(),
	    " [device-type]");
	fprintf(stderr, "where fsoptions are:\n");
	fprintf(stderr, "\t-E Erase previous disk content\n");
	fprintf(stderr, "\t-J Enable journaling via gjournal\n");
	fprintf(stderr, "\t-L volume label to add to superblock\n");
	fprintf(stderr,
	    "\t-N do not create file system, just print out parameters\n");
	fprintf(stderr, "\t-O file system format: 1 => UFS1, 2 => UFS2\n");
	fprintf(stderr, "\t-R regression test, suppress random factors\n");
	fprintf(stderr, "\t-S sector size\n");
	fprintf(stderr, "\t-T disktype\n");
	fprintf(stderr, "\t-U enable soft updates\n");
	fprintf(stderr, "\t-a maximum contiguous blocks\n");
	fprintf(stderr, "\t-b block size\n");
	fprintf(stderr, "\t-c blocks per cylinders group\n");
	fprintf(stderr, "\t-d maximum extent size\n");
	fprintf(stderr, "\t-e maximum blocks per file in a cylinder group\n");
	fprintf(stderr, "\t-f frag size\n");
	fprintf(stderr, "\t-g average file size\n");
	fprintf(stderr, "\t-h average files per directory\n");
	fprintf(stderr, "\t-i number of bytes per inode\n");
	fprintf(stderr, "\t-j enable soft updates journaling\n");
	fprintf(stderr, "\t-k space to hold for metadata blocks\n");
	fprintf(stderr, "\t-l enable multilabel MAC\n");
	fprintf(stderr, "\t-n do not create .snap directory\n");
	fprintf(stderr, "\t-m minimum free space %%\n");
	fprintf(stderr, "\t-o optimization preference (`space' or `time')\n");
	fprintf(stderr, "\t-p partition name (a..h)\n");
	fprintf(stderr, "\t-r reserved sectors at the end of device\n");
	fprintf(stderr, "\t-s file system size (sectors)\n");
	fprintf(stderr, "\t-t enable TRIM\n");
	exit(1);
}