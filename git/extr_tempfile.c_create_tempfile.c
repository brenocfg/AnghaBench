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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct tempfile {scalar_t__ fd; TYPE_1__ filename; } ;

/* Variables and functions */
 int EINVAL ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  activate_tempfile (struct tempfile*) ; 
 scalar_t__ adjust_shared_perm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deactivate_tempfile (struct tempfile*) ; 
 int /*<<< orphan*/  delete_tempfile (struct tempfile**) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 struct tempfile* new_tempfile () ; 
 void* open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  strbuf_add_absolute_path (TYPE_1__*,char const*) ; 

struct tempfile *create_tempfile(const char *path)
{
	struct tempfile *tempfile = new_tempfile();

	strbuf_add_absolute_path(&tempfile->filename, path);
	tempfile->fd = open(tempfile->filename.buf,
			    O_RDWR | O_CREAT | O_EXCL | O_CLOEXEC, 0666);
	if (O_CLOEXEC && tempfile->fd < 0 && errno == EINVAL)
		/* Try again w/o O_CLOEXEC: the kernel might not support it */
		tempfile->fd = open(tempfile->filename.buf,
				    O_RDWR | O_CREAT | O_EXCL, 0666);
	if (tempfile->fd < 0) {
		deactivate_tempfile(tempfile);
		return NULL;
	}
	activate_tempfile(tempfile);
	if (adjust_shared_perm(tempfile->filename.buf)) {
		int save_errno = errno;
		error("cannot fix permission bits on %s", tempfile->filename.buf);
		delete_tempfile(&tempfile);
		errno = save_errno;
		return NULL;
	}

	return tempfile;
}