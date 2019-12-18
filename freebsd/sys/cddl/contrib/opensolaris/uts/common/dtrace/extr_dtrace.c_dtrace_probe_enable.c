#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zoneid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  dtrace_probekey_t ;
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
struct TYPE_12__ {TYPE_2__* dten_vstate; } ;
typedef  TYPE_4__ dtrace_enabling_t ;
struct TYPE_9__ {int /*<<< orphan*/  dcr_cred; } ;
struct TYPE_11__ {TYPE_1__ dts_cred; } ;
struct TYPE_10__ {TYPE_3__* dtvs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_cred2priv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtrace_ecb_create_cache ; 
 int /*<<< orphan*/  dtrace_ecb_create_enable (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,TYPE_4__*),TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_probekey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_probe_enable(dtrace_probedesc_t *desc, dtrace_enabling_t *enab)
{
	dtrace_probekey_t pkey;
	uint32_t priv;
	uid_t uid;
	zoneid_t zoneid;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	dtrace_ecb_create_cache = NULL;

	if (desc == NULL) {
		/*
		 * If we're passed a NULL description, we're being asked to
		 * create an ECB with a NULL probe.
		 */
		(void) dtrace_ecb_create_enable(NULL, enab);
		return (0);
	}

	dtrace_probekey(desc, &pkey);
	dtrace_cred2priv(enab->dten_vstate->dtvs_state->dts_cred.dcr_cred,
	    &priv, &uid, &zoneid);

	return (dtrace_match(&pkey, priv, uid, zoneid, dtrace_ecb_create_enable,
	    enab));
}