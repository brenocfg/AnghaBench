#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct pipe {TYPE_1__ pipe_sel; } ;
struct knote {struct pipe* kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 

__attribute__((used)) static void
filt_pipedetach(struct knote *kn)
{
	struct pipe *cpipe = kn->kn_hook;

	PIPE_LOCK(cpipe);
	knlist_remove(&cpipe->pipe_sel.si_note, kn, 1);
	PIPE_UNLOCK(cpipe);
}