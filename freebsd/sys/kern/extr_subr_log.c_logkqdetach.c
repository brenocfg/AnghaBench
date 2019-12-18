#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knote {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {TYPE_1__ sc_selp; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 
 TYPE_2__ logsoftc ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
logkqdetach(struct knote *kn)
{

	mtx_lock(&msgbuf_lock);
	knlist_remove(&logsoftc.sc_selp.si_note, kn, 1);
	mtx_unlock(&msgbuf_lock);
}