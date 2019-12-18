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
struct dn_sch_inst {scalar_t__ credit; TYPE_1__* sched; } ;
struct dn_link {int /*<<< orphan*/  bandwidth; scalar_t__ burst; } ;
struct TYPE_4__ {scalar_t__ io_fast; } ;
struct TYPE_3__ {struct dn_link link; } ;

/* Variables and functions */
 TYPE_2__ dn_cfg ; 

__attribute__((used)) static int
si_reset_credit(void *_si, void *arg)
{
	struct dn_sch_inst *si = _si;
	struct dn_link *p = &si->sched->link;

	si->credit = p->burst + (dn_cfg.io_fast ?  p->bandwidth : 0);
	return 0;
}