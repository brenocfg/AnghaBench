#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  entries; } ;
typedef  TYPE_1__ git_mailmap ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mailmap_entry_cmp ; 

int git_mailmap_new(git_mailmap **out)
{
	int error;
	git_mailmap *mm = git__calloc(1, sizeof(git_mailmap));
	GIT_ERROR_CHECK_ALLOC(mm);

	error = git_vector_init(&mm->entries, 0, mailmap_entry_cmp);
	if (error < 0) {
		git__free(mm);
		return error;
	}
	*out = mm;
	return 0;
}