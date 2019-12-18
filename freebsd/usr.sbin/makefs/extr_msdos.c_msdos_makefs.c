#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vnode {TYPE_1__* fs; } ;
struct timeval {int dummy; } ;
struct msdosfsmount {int dummy; } ;
struct TYPE_6__ {scalar_t__ offset; int bytes_per_sector; int /*<<< orphan*/  create_size; } ;
struct msdos_options_ex {TYPE_4__ options; } ;
typedef  int /*<<< orphan*/  fsnode ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ maxsize; scalar_t__ offset; int sectorsize; int /*<<< orphan*/  fd; struct msdos_options_ex* fs_specific; } ;
typedef  TYPE_1__ fsinfo_t ;

/* Variables and functions */
 int DEBUG_FS_MAKEFS ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  TIMER_RESULTS (struct timeval,char*) ; 
 int /*<<< orphan*/  TIMER_START (struct timeval) ; 
 int /*<<< orphan*/  VTODE (struct vnode*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcleanup () ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int mkfs_msdos (char const*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int msdos_populate_dir (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ msdosfs_fsiflush (struct msdosfsmount*) ; 
 struct msdosfsmount* msdosfs_mount (struct vnode*) ; 
 scalar_t__ msdosfs_root (struct msdosfsmount*,struct vnode*) ; 
 int /*<<< orphan*/  open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

void
msdos_makefs(const char *image, const char *dir, fsnode *root, fsinfo_t *fsopts)
{
	struct msdos_options_ex *msdos_opt = fsopts->fs_specific;
	struct vnode vp, rootvp;
	struct timeval start;
	struct msdosfsmount *pmp;
	uint32_t flags;

	assert(image != NULL);
	assert(dir != NULL);
	assert(root != NULL);
	assert(fsopts != NULL);

	fsopts->size = fsopts->maxsize;
	msdos_opt->options.create_size = MAX(msdos_opt->options.create_size,
	    fsopts->offset + fsopts->size);
	if (fsopts->offset > 0)
		msdos_opt->options.offset = fsopts->offset;
	if (msdos_opt->options.bytes_per_sector == 0) {
		if (fsopts->sectorsize == -1)
			fsopts->sectorsize = 512;
		msdos_opt->options.bytes_per_sector = fsopts->sectorsize;
	} else if (fsopts->sectorsize == -1) {
		fsopts->sectorsize = msdos_opt->options.bytes_per_sector;
	} else if (fsopts->sectorsize != msdos_opt->options.bytes_per_sector) {
		err(1, "inconsistent sectorsize -S %u"
		    "!= -o bytes_per_sector %u",
		    fsopts->sectorsize, msdos_opt->options.bytes_per_sector);
	}

	/* create image */
	printf("Creating `%s'\n", image);
	TIMER_START(start);
	if (mkfs_msdos(image, NULL, &msdos_opt->options) == -1)
		return;
	TIMER_RESULTS(start, "mkfs_msdos");

	fsopts->fd = open(image, O_RDWR);
	vp.fs = fsopts;

	flags = 0;
	if ((pmp = msdosfs_mount(&vp)) == NULL)
		err(1, "msdosfs_mount");

	if (msdosfs_root(pmp, &rootvp) != 0)
		err(1, "msdosfs_root");

	if (debug & DEBUG_FS_MAKEFS)
		printf("msdos_makefs: image %s directory %s root %p\n",
		    image, dir, root);

	/* populate image */
	printf("Populating `%s'\n", image);
	TIMER_START(start);
	if (msdos_populate_dir(dir, VTODE(&rootvp), root, root, fsopts) == -1)
		errx(1, "Image file `%s' not created.", image);
	TIMER_RESULTS(start, "msdos_populate_dir");

	if (msdosfs_fsiflush(pmp) != 0)
		errx(1, "Unable to update FSInfo block.");
	if (debug & DEBUG_FS_MAKEFS)
		putchar('\n');

	/* ensure no outstanding buffers remain */
	if (debug & DEBUG_FS_MAKEFS)
		bcleanup();

	printf("Image `%s' complete\n", image);
}