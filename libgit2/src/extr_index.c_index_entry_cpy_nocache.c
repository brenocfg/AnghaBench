#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags_extended; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int GIT_INDEX_ENTRY_EXTENDED_FLAGS ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void index_entry_cpy_nocache(
	git_index_entry *tgt,
	const git_index_entry *src)
{
	git_oid_cpy(&tgt->id, &src->id);
	tgt->mode = src->mode;
	tgt->flags = src->flags;
	tgt->flags_extended = (src->flags_extended & GIT_INDEX_ENTRY_EXTENDED_FLAGS);
}