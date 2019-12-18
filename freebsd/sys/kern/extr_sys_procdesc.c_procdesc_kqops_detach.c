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
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct procdesc {TYPE_2__ pd_selinfo; } ;
struct knote {TYPE_1__* kn_fp; } ;
struct TYPE_3__ {struct procdesc* f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
procdesc_kqops_detach(struct knote *kn)
{
	struct procdesc *pd;

	pd = kn->kn_fp->f_data;
	knlist_remove(&pd->pd_selinfo.si_note, kn, 0);
}