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
struct cuse_server {TYPE_1__ selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 

__attribute__((used)) static void
cuse_server_wakeup_locked(struct cuse_server *pcs)
{
	selwakeup(&pcs->selinfo);
	KNOTE_LOCKED(&pcs->selinfo.si_note, 0);
}