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
struct TYPE_2__ {int /*<<< orphan*/  ut_name; } ;
struct tarfile {scalar_t__ tf_fp; TYPE_1__ tf_hdr; } ;
struct open_file {scalar_t__ f_flags; struct tarfile* f_fsdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EPERM ; 
 scalar_t__ F_READ ; 
 int errno ; 
 int /*<<< orphan*/ * package ; 
 struct tarfile* scan_tarfile (int /*<<< orphan*/ *,struct tarfile*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pkg_open(const char *fn, struct open_file *f)
{
	struct tarfile *tf;

	if (fn == NULL || f == NULL)
		return (EINVAL);

	if (package == NULL)
		return (ENXIO);

	/*
	 * We can only read from a package, so reject request to open
	 * for write-only or read-write.
	 */
	if (f->f_flags != F_READ)
		return (EPERM);

	/*
	 * Scan the file headers for the named file. We stop scanning
	 * at the first filename that has the .pkg extension. This is
	 * a package within a package. We assume we have all the files
	 * we need up-front and without having to dig within nested
	 * packages.
	 *
	 * Note that we preserve streaming properties as much as possible.
	 */
	while (*fn == '/')
		fn++;

	/*
	 * Allow opening of the root directory for use by readdir()
	 * to support listing files in the package.
	 */
	if (*fn == '\0') {
		f->f_fsdata = NULL;
		return (0);
	}

	tf = scan_tarfile(package, NULL);
	while (tf != NULL) {
		if (strcmp(fn, tf->tf_hdr.ut_name) == 0) {
			f->f_fsdata = tf;
			tf->tf_fp = 0;	/* Reset the file pointer. */
			return (0);
		}
		tf = scan_tarfile(package, tf);
	}
	return (errno);
}