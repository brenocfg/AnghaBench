#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dtpk_id; int /*<<< orphan*/ * dtpk_fmatch; int /*<<< orphan*/ * dtpk_nmatch; int /*<<< orphan*/ * dtpk_mmatch; int /*<<< orphan*/ * dtpk_pmatch; int /*<<< orphan*/  dtpk_name; int /*<<< orphan*/  dtpk_func; int /*<<< orphan*/  dtpk_mod; int /*<<< orphan*/  dtpk_prov; } ;
typedef  TYPE_1__ dtrace_probekey_t ;
struct TYPE_6__ {scalar_t__ dtpd_id; int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; int /*<<< orphan*/  dtpd_provider; } ;
typedef  TYPE_2__ dtrace_probedesc_t ;

/* Variables and functions */
 scalar_t__ DTRACE_IDNONE ; 
 int /*<<< orphan*/  dtrace_match_nonzero ; 
 int /*<<< orphan*/  dtrace_match_nul ; 
 void* dtrace_probekey_func (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_probekey(dtrace_probedesc_t *pdp, dtrace_probekey_t *pkp)
{
	pkp->dtpk_prov = pdp->dtpd_provider;
	pkp->dtpk_pmatch = dtrace_probekey_func(pdp->dtpd_provider);

	pkp->dtpk_mod = pdp->dtpd_mod;
	pkp->dtpk_mmatch = dtrace_probekey_func(pdp->dtpd_mod);

	pkp->dtpk_func = pdp->dtpd_func;
	pkp->dtpk_fmatch = dtrace_probekey_func(pdp->dtpd_func);

	pkp->dtpk_name = pdp->dtpd_name;
	pkp->dtpk_nmatch = dtrace_probekey_func(pdp->dtpd_name);

	pkp->dtpk_id = pdp->dtpd_id;

	if (pkp->dtpk_id == DTRACE_IDNONE &&
	    pkp->dtpk_pmatch == &dtrace_match_nul &&
	    pkp->dtpk_mmatch == &dtrace_match_nul &&
	    pkp->dtpk_fmatch == &dtrace_match_nul &&
	    pkp->dtpk_nmatch == &dtrace_match_nul)
		pkp->dtpk_fmatch = &dtrace_match_nonzero;
}