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
typedef  scalar_t__ uid_t ;
struct uidinfo {scalar_t__ ui_uid; int /*<<< orphan*/  ui_racct; int /*<<< orphan*/  ui_ref; } ;
struct ucred {struct uidinfo* cr_ruidinfo; struct uidinfo* cr_uidinfo; } ;
struct TYPE_2__ {struct ucred* td_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct uidinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_UIDINFO ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  UIHASH (scalar_t__) ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  free (struct uidinfo*,int /*<<< orphan*/ ) ; 
 struct uidinfo* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  racct_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  racct_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_hash ; 
 int /*<<< orphan*/  uihashtbl_lock ; 
 int /*<<< orphan*/  uihold (struct uidinfo*) ; 
 struct uidinfo* uilookup (scalar_t__) ; 

struct uidinfo *
uifind(uid_t uid)
{
	struct uidinfo *new_uip, *uip;
	struct ucred *cred;

	cred = curthread->td_ucred;
	if (cred->cr_uidinfo->ui_uid == uid) {
		uip = cred->cr_uidinfo;
		uihold(uip);
		return (uip);
	} else if (cred->cr_ruidinfo->ui_uid == uid) {
		uip = cred->cr_ruidinfo;
		uihold(uip);
		return (uip);
	}

	rw_rlock(&uihashtbl_lock);
	uip = uilookup(uid);
	rw_runlock(&uihashtbl_lock);
	if (uip != NULL)
		return (uip);

	new_uip = malloc(sizeof(*new_uip), M_UIDINFO, M_WAITOK | M_ZERO);
	racct_create(&new_uip->ui_racct);
	refcount_init(&new_uip->ui_ref, 1);
	new_uip->ui_uid = uid;

	rw_wlock(&uihashtbl_lock);
	/*
	 * There's a chance someone created our uidinfo while we
	 * were in malloc and not holding the lock, so we have to
	 * make sure we don't insert a duplicate uidinfo.
	 */
	if ((uip = uilookup(uid)) == NULL) {
		LIST_INSERT_HEAD(UIHASH(uid), new_uip, ui_hash);
		rw_wunlock(&uihashtbl_lock);
		uip = new_uip;
	} else {
		rw_wunlock(&uihashtbl_lock);
		racct_destroy(&new_uip->ui_racct);
		free(new_uip, M_UIDINFO);
	}
	return (uip);
}