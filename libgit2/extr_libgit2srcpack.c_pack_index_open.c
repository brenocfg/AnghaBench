#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct git_pack_file {int index_version; char* pack_name; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 scalar_t__ git_buf_init (TYPE_1__*,size_t) ; 
 scalar_t__ git_buf_oom (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_put (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  git_buf_puts (TYPE_1__*,char*) ; 
 int git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 int pack_index_check (int /*<<< orphan*/ ,struct git_pack_file*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int pack_index_open(struct git_pack_file *p)
{
	int error = 0;
	size_t name_len;
	git_buf idx_name;

	if (p->index_version > -1)
		return 0;

	name_len = strlen(p->pack_name);
	assert(name_len > strlen(".pack")); /* checked by git_pack_file alloc */

	if (git_buf_init(&idx_name, name_len) < 0)
		return -1;

	git_buf_put(&idx_name, p->pack_name, name_len - strlen(".pack"));
	git_buf_puts(&idx_name, ".idx");
	if (git_buf_oom(&idx_name)) {
		git_buf_dispose(&idx_name);
		return -1;
	}

	if ((error = git_mutex_lock(&p->lock)) < 0) {
		git_buf_dispose(&idx_name);
		return error;
	}

	if (p->index_version == -1)
		error = pack_index_check(idx_name.ptr, p);

	git_buf_dispose(&idx_name);

	git_mutex_unlock(&p->lock);

	return error;
}