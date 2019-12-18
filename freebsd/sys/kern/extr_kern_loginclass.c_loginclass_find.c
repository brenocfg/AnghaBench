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
struct loginclass {int /*<<< orphan*/  lc_racct; int /*<<< orphan*/  lc_name; int /*<<< orphan*/  lc_refcount; } ;
struct TYPE_4__ {TYPE_1__* td_ucred; } ;
struct TYPE_3__ {struct loginclass* cr_loginclass; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct loginclass*,int /*<<< orphan*/ ) ; 
 scalar_t__ MAXLOGNAME ; 
 int /*<<< orphan*/  M_LOGINCLASS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 TYPE_2__* curthread ; 
 int /*<<< orphan*/  free (struct loginclass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lc_next ; 
 int /*<<< orphan*/  loginclass_hold (struct loginclass*) ; 
 struct loginclass* loginclass_lookup (char const*) ; 
 int /*<<< orphan*/  loginclasses ; 
 int /*<<< orphan*/  loginclasses_lock ; 
 struct loginclass* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  racct_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  racct_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct loginclass *
loginclass_find(const char *name)
{
	struct loginclass *lc, *new_lc;

	if (name[0] == '\0' || strlen(name) >= MAXLOGNAME)
		return (NULL);

	lc = curthread->td_ucred->cr_loginclass;
	if (strcmp(name, lc->lc_name) == 0) {
		loginclass_hold(lc);
		return (lc);
	}

	rw_rlock(&loginclasses_lock);
	lc = loginclass_lookup(name);
	rw_runlock(&loginclasses_lock);
	if (lc != NULL)
		return (lc);

	new_lc = malloc(sizeof(*new_lc), M_LOGINCLASS, M_ZERO | M_WAITOK);
	racct_create(&new_lc->lc_racct);
	refcount_init(&new_lc->lc_refcount, 1);
	strcpy(new_lc->lc_name, name);

	rw_wlock(&loginclasses_lock);
	/*
	 * There's a chance someone created our loginclass while we
	 * were in malloc and not holding the lock, so we have to
	 * make sure we don't insert a duplicate loginclass.
	 */
	if ((lc = loginclass_lookup(name)) == NULL) {
		LIST_INSERT_HEAD(&loginclasses, new_lc, lc_next);
		rw_wunlock(&loginclasses_lock);
		lc = new_lc;
	} else {
		rw_wunlock(&loginclasses_lock);
		racct_destroy(&new_lc->lc_racct);
		free(new_lc, M_LOGINCLASS);
	}

	return (lc);
}