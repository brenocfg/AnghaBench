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
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (TYPE_1__*) ;int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ git_reference_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFCOUNT_DEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refdb__free ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void git_refdb_iterator_free(git_reference_iterator *iter)
{
	GIT_REFCOUNT_DEC(iter->db, git_refdb__free);
	iter->free(iter);
}