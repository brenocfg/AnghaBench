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
struct TYPE_4__ {struct TYPE_4__* theirs; struct TYPE_4__* ours; struct TYPE_4__* ancestor; } ;
typedef  TYPE_1__ git_index_name_entry ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

__attribute__((used)) static void index_name_entry_free(git_index_name_entry *ne)
{
	if (!ne)
		return;
	git__free(ne->ancestor);
	git__free(ne->ours);
	git__free(ne->theirs);
	git__free(ne);
}