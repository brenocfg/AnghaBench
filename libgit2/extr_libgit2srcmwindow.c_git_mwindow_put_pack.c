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
struct git_pack_file {int /*<<< orphan*/  pack_name; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__mwindow_mutex ; 
 int /*<<< orphan*/  git__pack_cache ; 
 int git_atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ git_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_packfile_free (struct git_pack_file*) ; 
 int /*<<< orphan*/  git_strmap_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strmap_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void git_mwindow_put_pack(struct git_pack_file *pack)
{
	int count;

	if (git_mutex_lock(&git__mwindow_mutex) < 0)
		return;

	/* put before get would be a corrupted state */
	assert(git__pack_cache);

	/* if we cannot find it, the state is corrupted */
	assert(git_strmap_exists(git__pack_cache, pack->pack_name));

	count = git_atomic_dec(&pack->refcount);
	if (count == 0) {
		git_strmap_delete(git__pack_cache, pack->pack_name);
		git_packfile_free(pack);
	}

	git_mutex_unlock(&git__mwindow_mutex);
	return;
}