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
 int /*<<< orphan*/  close_tempfile_gently (struct tempfile*) ; 
 int /*<<< orphan*/  deactivate_tempfile (struct tempfile*) ; 
 int /*<<< orphan*/  is_tempfile_active (struct tempfile*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 

void delete_tempfile(struct tempfile **tempfile_p)
{
	struct tempfile *tempfile = *tempfile_p;

	if (!is_tempfile_active(tempfile))
		return;

	close_tempfile_gently(tempfile);
	unlink_or_warn(tempfile->filename.buf);
	deactivate_tempfile(tempfile);
	*tempfile_p = NULL;
}