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
struct cuse_server {int refs; TYPE_1__ selinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_server_is_closing (struct cuse_server*) ; 
 int /*<<< orphan*/  cuse_server_wakeup_all_client_locked (struct cuse_server*) ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
cuse_server_do_close(struct cuse_server *pcs)
{
	int retval;

	cuse_lock();
	cuse_server_is_closing(pcs);
	/* final client wakeup, if any */
	cuse_server_wakeup_all_client_locked(pcs);

	knlist_clear(&pcs->selinfo.si_note, 1);

	retval = pcs->refs;
	cuse_unlock();

	return (retval);
}