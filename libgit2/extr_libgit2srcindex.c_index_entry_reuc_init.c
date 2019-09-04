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
struct TYPE_5__ {int* mode; int /*<<< orphan*/ * oid; } ;
typedef  TYPE_1__ git_index_reuc_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 TYPE_1__* reuc_entry_alloc (char const*) ; 

__attribute__((used)) static int index_entry_reuc_init(git_index_reuc_entry **reuc_out,
	const char *path,
	int ancestor_mode, const git_oid *ancestor_oid,
	int our_mode, const git_oid *our_oid,
	int their_mode, const git_oid *their_oid)
{
	git_index_reuc_entry *reuc = NULL;

	assert(reuc_out && path);

	*reuc_out = reuc = reuc_entry_alloc(path);
	GIT_ERROR_CHECK_ALLOC(reuc);

	if ((reuc->mode[0] = ancestor_mode) > 0) {
		assert(ancestor_oid);
		git_oid_cpy(&reuc->oid[0], ancestor_oid);
	}

	if ((reuc->mode[1] = our_mode) > 0) {
		assert(our_oid);
		git_oid_cpy(&reuc->oid[1], our_oid);
	}

	if ((reuc->mode[2] = their_mode) > 0) {
		assert(their_oid);
		git_oid_cpy(&reuc->oid[2], their_oid);
	}

	return 0;
}