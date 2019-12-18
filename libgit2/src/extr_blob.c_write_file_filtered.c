#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_off_t ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_filter_list ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_filter_list_apply_to_file (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_file_filtered(
	git_oid *id,
	git_off_t *size,
	git_odb *odb,
	const char *full_path,
	git_filter_list *fl)
{
	int error;
	git_buf tgt = GIT_BUF_INIT;

	error = git_filter_list_apply_to_file(&tgt, fl, NULL, full_path);

	/* Write the file to disk if it was properly filtered */
	if (!error) {
		*size = tgt.size;

		error = git_odb_write(id, odb, tgt.ptr, tgt.size, GIT_OBJECT_BLOB);
	}

	git_buf_dispose(&tgt);
	return error;
}