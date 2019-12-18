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
struct tarfile {TYPE_1__ tf_hdr; } ;
struct open_file {scalar_t__ f_fsdata; } ;
struct dirent {int d_reclen; int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_type; scalar_t__ d_fileno; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_REG ; 
 int EBADF ; 
 int ENOENT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  package ; 
 struct tarfile* scan_tarfile (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pkg_readdir(struct open_file *f, struct dirent *d)
{
	struct tarfile *tf;

	tf = (struct tarfile *)f->f_fsdata;
	if (tf != NULL)
		return (EBADF);

	tf = scan_tarfile(package, NULL);
	if (tf == NULL)
		return (ENOENT);

	d->d_fileno = 0;
	d->d_reclen = sizeof(*d);
	d->d_type = DT_REG;
	memcpy(d->d_name, tf->tf_hdr.ut_name, sizeof(d->d_name));
	return (0);
}