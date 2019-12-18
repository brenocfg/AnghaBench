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
struct open_file {int f_flags; struct fs_ops* f_ops; TYPE_1__* f_dev; int /*<<< orphan*/ * f_rabuf; int /*<<< orphan*/ * f_devdata; scalar_t__ f_offset; } ;
struct fs_ops {int (* fo_open ) (char const*,struct open_file*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  (* dv_close ) (struct open_file*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EMFILE ; 
 int ENOENT ; 
 int F_NODEV ; 
 int F_RAW ; 
 int /*<<< orphan*/  devclose (struct open_file*) ; 
 int devopen (struct open_file*,char const*,char const**) ; 
 int errno ; 
 struct fs_ops* exclusive_file_system ; 
 struct fs_ops** file_system ; 
 struct open_file* files ; 
 int o_gethandle () ; 
 int /*<<< orphan*/  o_rainit (struct open_file*) ; 
 int stub1 (char const*,struct open_file*) ; 
 int stub2 (char const*,struct open_file*) ; 
 int /*<<< orphan*/  stub3 (struct open_file*) ; 

int
open(const char *fname, int mode)
{
	struct fs_ops *fs;
	struct open_file *f;
	int fd, i, error, besterror;
	const char *file;

	if ((fd = o_gethandle()) == -1) {
		errno = EMFILE;
		return (-1);
	}

	f = &files[fd];
	f->f_flags = mode + 1;
	f->f_dev = NULL;
	f->f_ops = NULL;
	f->f_offset = 0;
	f->f_devdata = NULL;
	file = NULL;

	if (exclusive_file_system != NULL) {
		fs = exclusive_file_system;
		error = (fs->fo_open)(fname, f);
		if (error == 0)
			goto ok;
		goto err;
	}

	error = devopen(f, fname, &file);
	if (error ||
	    (((f->f_flags & F_NODEV) == 0) && f->f_dev == NULL))
		goto err;

	/* see if we opened a raw device; otherwise, 'file' is the file name. */
	if (file == NULL || *file == '\0') {
		f->f_flags |= F_RAW;
		f->f_rabuf = NULL;
		return (fd);
	}

	/* pass file name to the different filesystem open routines */
	besterror = ENOENT;
	for (i = 0; file_system[i] != NULL; i++) {
		fs = file_system[i];
		error = (fs->fo_open)(file, f);
		if (error == 0)
			goto ok;
		if (error != EINVAL)
			besterror = error;
	}
	error = besterror;

	if ((f->f_flags & F_NODEV) == 0 && f->f_dev != NULL)
		f->f_dev->dv_close(f);
	if (error)
		devclose(f);

err:
	f->f_flags = 0;
	errno = error;
	return (-1);

ok:
	f->f_ops = fs;
	o_rainit(f);
	return (fd);
}