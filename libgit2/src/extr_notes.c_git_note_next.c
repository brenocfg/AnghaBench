#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_iterator_current (TYPE_1__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int process_entry_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_note_next(
	git_oid* note_id,
	git_oid* annotated_id,
	git_note_iterator *it)
{
	int error;
	const git_index_entry *item;

	if ((error = git_iterator_current(&item, it)) < 0)
		return error;

	git_oid_cpy(note_id, &item->id);

	if (!(error = process_entry_path(item->path, annotated_id)))
		git_iterator_advance(NULL, it);

	return error;
}