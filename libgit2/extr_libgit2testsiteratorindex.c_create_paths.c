#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_12__ {size_t size; char* ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_printf (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  git_buf_putc (TYPE_2__*,char) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  git_buf_truncate (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void create_paths(git_index *index, const char *root, int depth)
{
	git_buf fullpath = GIT_BUF_INIT;
	git_index_entry entry;
	size_t root_len;
	int i;

	if (root) {
		cl_git_pass(git_buf_puts(&fullpath, root));
		cl_git_pass(git_buf_putc(&fullpath, '/'));
	}

	root_len = fullpath.size;

	for (i = 0; i < 8; i++) {
		bool file = (depth == 0 || (i % 2) == 0);
		git_buf_truncate(&fullpath, root_len);
		cl_git_pass(git_buf_printf(&fullpath, "item%d", i));

		if (file) {
			memset(&entry, 0, sizeof(git_index_entry));
			entry.path = fullpath.ptr;
			entry.mode = GIT_FILEMODE_BLOB;
			git_oid_fromstr(&entry.id, "d44e18fb93b7107b5cd1b95d601591d77869a1b6");

			cl_git_pass(git_index_add(index, &entry));
		} else if (depth > 0) {
			create_paths(index, fullpath.ptr, (depth - 1));
		}
	}

	git_buf_dispose(&fullpath);
}