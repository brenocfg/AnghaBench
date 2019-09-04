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
struct lock_file {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct lock_file LOCK_INIT ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 int /*<<< orphan*/  dump_marks_helper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error_errno (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_marks_file ; 
 int /*<<< orphan*/  failure ; 
 int /*<<< orphan*/ * fdopen_lock_file (struct lock_file*,char*) ; 
 scalar_t__ hold_lock_file_for_update (struct lock_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ import_marks_file ; 
 int /*<<< orphan*/  import_marks_file_done ; 
 int /*<<< orphan*/  marks ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 char* strerror (int) ; 

__attribute__((used)) static void dump_marks(void)
{
	struct lock_file mark_lock = LOCK_INIT;
	FILE *f;

	if (!export_marks_file || (import_marks_file && !import_marks_file_done))
		return;

	if (hold_lock_file_for_update(&mark_lock, export_marks_file, 0) < 0) {
		failure |= error_errno("Unable to write marks file %s",
				       export_marks_file);
		return;
	}

	f = fdopen_lock_file(&mark_lock, "w");
	if (!f) {
		int saved_errno = errno;
		rollback_lock_file(&mark_lock);
		failure |= error("Unable to write marks file %s: %s",
			export_marks_file, strerror(saved_errno));
		return;
	}

	dump_marks_helper(f, 0, marks);
	if (commit_lock_file(&mark_lock)) {
		failure |= error_errno("Unable to write file %s",
				       export_marks_file);
		return;
	}
}