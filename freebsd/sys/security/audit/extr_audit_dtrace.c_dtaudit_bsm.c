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
struct kaudit_record {int /*<<< orphan*/  k_ar; scalar_t__ k_dtaudit_state; } ;
struct evname_elem {int /*<<< orphan*/  ene_bsm_probe_id; int /*<<< orphan*/ * ene_name; int /*<<< orphan*/  ene_bsm_probe_enabled; } ;
typedef  int /*<<< orphan*/  ene_name_lower ;
typedef  int /*<<< orphan*/  au_id_t ;
typedef  int /*<<< orphan*/  au_event_t ;
typedef  int /*<<< orphan*/  au_class_t ;

/* Variables and functions */
 int EVNAMEMAP_NAME_SIZE ; 
 int /*<<< orphan*/  EVNAME_LOCK (struct evname_elem*) ; 
 int /*<<< orphan*/  EVNAME_UNLOCK (struct evname_elem*) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,uintptr_t,uintptr_t,uintptr_t,uintptr_t,int /*<<< orphan*/ ) ; 
 char tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtaudit_bsm(struct kaudit_record *kar, au_id_t auid, au_event_t event,
    au_class_t class, int sorf, void *bsm_data, size_t bsm_len)
{
	char ene_name_lower[EVNAMEMAP_NAME_SIZE];
	struct evname_elem *ene;
	int i;

	ene = (struct evname_elem *)kar->k_dtaudit_state;
	if (ene == NULL)
		return;
	if (!(ene->ene_bsm_probe_enabled))
		return;

	/*
	 * XXXRW: Lock ene to provide stability to the name string.  A bit
	 * undesirable!  We may want another locking strategy here.  At least
	 * we don't run the DTrace probe under the lock.
	 *
	 * XXXRW: We provide the struct audit_record pointer -- but perhaps
	 * should provide the kaudit_record pointer?
	 */
	EVNAME_LOCK(ene);
	for (i = 0; i < sizeof(ene_name_lower); i++)
		ene_name_lower[i] = tolower(ene->ene_name[i]);
	EVNAME_UNLOCK(ene);
	dtrace_probe(ene->ene_bsm_probe_id, (uintptr_t)ene_name_lower,
	    (uintptr_t)&kar->k_ar, (uintptr_t)bsm_data, (uintptr_t)bsm_len,
	    0);
}