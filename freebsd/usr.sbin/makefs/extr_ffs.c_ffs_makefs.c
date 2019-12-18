#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  cs_nffree; int /*<<< orphan*/  cs_nifree; int /*<<< orphan*/  cs_nbfree; int /*<<< orphan*/  cs_ndir; } ;
struct TYPE_9__ {int /*<<< orphan*/  cs_nffree; int /*<<< orphan*/  cs_nifree; int /*<<< orphan*/  cs_nbfree; int /*<<< orphan*/  cs_ndir; } ;
struct fs {TYPE_2__ fs_cstotal; TYPE_1__ fs_old_cstotal; scalar_t__ fs_fmod; } ;
typedef  int /*<<< orphan*/  fsnode ;
struct TYPE_11__ {int fd; struct fs* superblock; int /*<<< orphan*/  curinode; scalar_t__ inodes; scalar_t__ size; } ;
typedef  TYPE_3__ fsinfo_t ;

/* Variables and functions */
 int DEBUG_FS_MAKEFS ; 
 int /*<<< orphan*/  TIMER_RESULTS (struct timeval,char*) ; 
 int /*<<< orphan*/  TIMER_START (struct timeval) ; 
 int /*<<< orphan*/  UFS_ROOTINO ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcleanup () ; 
 int close (int) ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int ffs_create_image (char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  ffs_populate_dir (char const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ffs_validate (char const*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ffs_write_superblock (struct fs*,TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

void
ffs_makefs(const char *image, const char *dir, fsnode *root, fsinfo_t *fsopts)
{
	struct fs	*superblock;
	struct timeval	start;

	assert(image != NULL);
	assert(dir != NULL);
	assert(root != NULL);
	assert(fsopts != NULL);

	if (debug & DEBUG_FS_MAKEFS)
		printf("ffs_makefs: image %s directory %s root %p\n",
		    image, dir, root);

		/* validate tree and options */
	TIMER_START(start);
	ffs_validate(dir, root, fsopts);
	TIMER_RESULTS(start, "ffs_validate");

	printf("Calculated size of `%s': %lld bytes, %lld inodes\n",
	    image, (long long)fsopts->size, (long long)fsopts->inodes);

		/* create image */
	TIMER_START(start);
	if (ffs_create_image(image, fsopts) == -1)
		errx(1, "Image file `%s' not created.", image);
	TIMER_RESULTS(start, "ffs_create_image");

	fsopts->curinode = UFS_ROOTINO;

	if (debug & DEBUG_FS_MAKEFS)
		putchar('\n');

		/* populate image */
	printf("Populating `%s'\n", image);
	TIMER_START(start);
	if (! ffs_populate_dir(dir, root, fsopts))
		errx(1, "Image file `%s' not populated.", image);
	TIMER_RESULTS(start, "ffs_populate_dir");

		/* ensure no outstanding buffers remain */
	if (debug & DEBUG_FS_MAKEFS)
		bcleanup();

		/* update various superblock parameters */
	superblock = fsopts->superblock;
	superblock->fs_fmod = 0;
	superblock->fs_old_cstotal.cs_ndir   = superblock->fs_cstotal.cs_ndir;
	superblock->fs_old_cstotal.cs_nbfree = superblock->fs_cstotal.cs_nbfree;
	superblock->fs_old_cstotal.cs_nifree = superblock->fs_cstotal.cs_nifree;
	superblock->fs_old_cstotal.cs_nffree = superblock->fs_cstotal.cs_nffree;

		/* write out superblock; image is now complete */
	ffs_write_superblock(fsopts->superblock, fsopts);
	if (close(fsopts->fd) == -1)
		err(1, "Closing `%s'", image);
	fsopts->fd = -1;
	printf("Image `%s' complete\n", image);
}