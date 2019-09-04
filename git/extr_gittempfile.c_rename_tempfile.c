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
struct tempfile {TYPE_1__ filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ close_tempfile_gently (struct tempfile*) ; 
 int /*<<< orphan*/  deactivate_tempfile (struct tempfile*) ; 
 int /*<<< orphan*/  delete_tempfile (struct tempfile**) ; 
 int errno ; 
 int /*<<< orphan*/  is_tempfile_active (struct tempfile*) ; 
 scalar_t__ rename (int /*<<< orphan*/ ,char const*) ; 

int rename_tempfile(struct tempfile **tempfile_p, const char *path)
{
	struct tempfile *tempfile = *tempfile_p;

	if (!is_tempfile_active(tempfile))
		BUG("rename_tempfile called for inactive object");

	if (close_tempfile_gently(tempfile)) {
		delete_tempfile(tempfile_p);
		return -1;
	}

	if (rename(tempfile->filename.buf, path)) {
		int save_errno = errno;
		delete_tempfile(tempfile_p);
		errno = save_errno;
		return -1;
	}

	deactivate_tempfile(tempfile);
	*tempfile_p = NULL;
	return 0;
}