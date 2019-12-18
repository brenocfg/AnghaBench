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
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_7__ {int /*<<< orphan*/  head_detached; scalar_t__ inmemory; } ;
typedef  TYPE_1__ git_rebase ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int rebase_cleanup (TYPE_1__*) ; 
 int rebase_copy_notes (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int return_to_orig_head (TYPE_1__*) ; 

int git_rebase_finish(
	git_rebase *rebase,
	const git_signature *signature)
{
	int error = 0;

	assert(rebase);

	if (rebase->inmemory)
		return 0;

	if (!rebase->head_detached)
		error = return_to_orig_head(rebase);

	if (error == 0 && (error = rebase_copy_notes(rebase, signature)) == 0)
		error = rebase_cleanup(rebase);

	return error;
}