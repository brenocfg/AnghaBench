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
struct stat {scalar_t__ st_size; } ;
struct TYPE_2__ {int bootinst_size; int /*<<< orphan*/ * bootinst; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 char* b_flag ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 TYPE_1__ mboot ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int secsize ; 

__attribute__((used)) static void
init_boot(void)
{
	const char *fname;
	int fdesc, n;
	struct stat sb;

	fname = b_flag ? b_flag : "/boot/mbr";
	if ((fdesc = open(fname, O_RDONLY)) == -1 ||
	    fstat(fdesc, &sb) == -1)
		err(1, "%s", fname);
	if (sb.st_size == 0)
		errx(1, "%s is empty, must not be.", fname);
	if ((mboot.bootinst_size = sb.st_size) % secsize != 0)
		errx(1, "%s: length must be a multiple of sector size", fname);
	if (mboot.bootinst != NULL)
		free(mboot.bootinst);
	if ((mboot.bootinst = malloc(mboot.bootinst_size = sb.st_size)) == NULL)
		errx(1, "%s: unable to allocate read buffer", fname);
	if ((n = read(fdesc, mboot.bootinst, mboot.bootinst_size)) == -1 ||
	    close(fdesc))
		err(1, "%s", fname);
	if (n != mboot.bootinst_size)
		errx(1, "%s: short read", fname);
}