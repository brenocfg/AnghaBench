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
struct uidinfo {scalar_t__ ui_sbsize; int ui_uid; scalar_t__ ui_proccnt; scalar_t__ ui_vmsize; int /*<<< orphan*/  ui_racct; int /*<<< orphan*/  ui_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct uidinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_UIDINFO ; 
 int /*<<< orphan*/  free (struct uidinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned long long) ; 
 int /*<<< orphan*/  racct_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release_if_not_last (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_hash ; 
 int /*<<< orphan*/  uihashtbl_lock ; 

void
uifree(struct uidinfo *uip)
{

	if (refcount_release_if_not_last(&uip->ui_ref))
		return;

	rw_wlock(&uihashtbl_lock);
	if (refcount_release(&uip->ui_ref) == 0) {
		rw_wunlock(&uihashtbl_lock);
		return;
	}

	racct_destroy(&uip->ui_racct);
	LIST_REMOVE(uip, ui_hash);
	rw_wunlock(&uihashtbl_lock);

	if (uip->ui_sbsize != 0)
		printf("freeing uidinfo: uid = %d, sbsize = %ld\n",
		    uip->ui_uid, uip->ui_sbsize);
	if (uip->ui_proccnt != 0)
		printf("freeing uidinfo: uid = %d, proccnt = %ld\n",
		    uip->ui_uid, uip->ui_proccnt);
	if (uip->ui_vmsize != 0)
		printf("freeing uidinfo: uid = %d, swapuse = %lld\n",
		    uip->ui_uid, (unsigned long long)uip->ui_vmsize);
	free(uip, M_UIDINFO);
}