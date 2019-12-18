#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dtpv_name; } ;
typedef  TYPE_1__ dtrace_provider_t ;
typedef  scalar_t__ dtrace_provider_id_t ;
struct TYPE_5__ {char* dtpk_mod; char* dtpk_func; char* dtpk_name; int /*<<< orphan*/  dtpk_id; int /*<<< orphan*/ * dtpk_nmatch; int /*<<< orphan*/ * dtpk_fmatch; int /*<<< orphan*/ * dtpk_mmatch; int /*<<< orphan*/ * dtpk_pmatch; int /*<<< orphan*/  dtpk_prov; } ;
typedef  TYPE_2__ dtrace_probekey_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_IDNONE ; 
 int /*<<< orphan*/  DTRACE_PRIV_ALL ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int dtrace_match (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_match_nul ; 
 int /*<<< orphan*/  dtrace_match_string ; 
 int /*<<< orphan*/  dtrace_probe_lookup_match ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

dtrace_id_t
dtrace_probe_lookup(dtrace_provider_id_t prid, char *mod,
    char *func, char *name)
{
	dtrace_probekey_t pkey;
	dtrace_id_t id;
	int match;

	pkey.dtpk_prov = ((dtrace_provider_t *)prid)->dtpv_name;
	pkey.dtpk_pmatch = &dtrace_match_string;
	pkey.dtpk_mod = mod;
	pkey.dtpk_mmatch = mod ? &dtrace_match_string : &dtrace_match_nul;
	pkey.dtpk_func = func;
	pkey.dtpk_fmatch = func ? &dtrace_match_string : &dtrace_match_nul;
	pkey.dtpk_name = name;
	pkey.dtpk_nmatch = name ? &dtrace_match_string : &dtrace_match_nul;
	pkey.dtpk_id = DTRACE_IDNONE;

	mutex_enter(&dtrace_lock);
	match = dtrace_match(&pkey, DTRACE_PRIV_ALL, 0, 0,
	    dtrace_probe_lookup_match, &id);
	mutex_exit(&dtrace_lock);

	ASSERT(match == 1 || match == 0);
	return (match ? id : 0);
}