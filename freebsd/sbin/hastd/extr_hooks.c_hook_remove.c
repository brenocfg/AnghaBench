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
struct hookproc {scalar_t__ hp_magic; scalar_t__ hp_pid; } ;

/* Variables and functions */
 scalar_t__ HOOKPROC_MAGIC_ALLOCATED ; 
 scalar_t__ HOOKPROC_MAGIC_ONLIST ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct hookproc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hookprocs ; 
 int /*<<< orphan*/  hookprocs_lock ; 
 int /*<<< orphan*/  hp_next ; 
 int mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hook_remove(struct hookproc *hp)
{

	PJDLOG_ASSERT(hp->hp_magic == HOOKPROC_MAGIC_ONLIST);
	PJDLOG_ASSERT(hp->hp_pid > 0);
	PJDLOG_ASSERT(mtx_owned(&hookprocs_lock));

	TAILQ_REMOVE(&hookprocs, hp, hp_next);
	hp->hp_magic = HOOKPROC_MAGIC_ALLOCATED;
}