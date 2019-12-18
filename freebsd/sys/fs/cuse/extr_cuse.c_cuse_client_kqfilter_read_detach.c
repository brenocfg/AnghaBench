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
struct knote {struct cuse_client* kn_hook; } ;
struct cuse_client {TYPE_2__* server; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {TYPE_1__ selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int) ; 

__attribute__((used)) static void
cuse_client_kqfilter_read_detach(struct knote *kn)
{
	struct cuse_client *pcc;

	cuse_lock();
	pcc = kn->kn_hook;
	knlist_remove(&pcc->server->selinfo.si_note, kn, 1);
	cuse_unlock();
}