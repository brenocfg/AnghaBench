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
struct ptunit_suite {int dummy; } ;
struct fetch_fixture {int /*<<< orphan*/  fini; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  fetch_empty ; 
 int /*<<< orphan*/  fetch_exstop_ip ; 
 int /*<<< orphan*/  fetch_mode_exec ; 
 int /*<<< orphan*/  fetch_mode_tsx ; 
 int /*<<< orphan*/  fetch_null ; 
 int /*<<< orphan*/  fetch_tnt_8 ; 
 int /*<<< orphan*/  fetch_type ; 
 int /*<<< orphan*/  fetch_unknown ; 
 int /*<<< orphan*/  fetch_unknown_ext ; 
 int /*<<< orphan*/  fetch_unknown_ext2 ; 
 int /*<<< orphan*/  ffix_fini ; 
 int /*<<< orphan*/  ffix_init ; 
 int /*<<< orphan*/  ppt_cbr ; 
 int /*<<< orphan*/  ppt_cyc ; 
 int /*<<< orphan*/  ppt_exstop ; 
 int /*<<< orphan*/  ppt_fup ; 
 int /*<<< orphan*/  ppt_mnt ; 
 int /*<<< orphan*/  ppt_mtc ; 
 int /*<<< orphan*/  ppt_mwait ; 
 int /*<<< orphan*/  ppt_ovf ; 
 int /*<<< orphan*/  ppt_pad ; 
 int /*<<< orphan*/  ppt_pip ; 
 int /*<<< orphan*/  ppt_psb ; 
 int /*<<< orphan*/  ppt_psbend ; 
 int /*<<< orphan*/  ppt_ptw ; 
 int /*<<< orphan*/  ppt_pwre ; 
 int /*<<< orphan*/  ppt_pwrx ; 
 int /*<<< orphan*/  ppt_stop ; 
 int /*<<< orphan*/  ppt_tip ; 
 int /*<<< orphan*/  ppt_tip_pgd ; 
 int /*<<< orphan*/  ppt_tip_pge ; 
 int /*<<< orphan*/  ppt_tma ; 
 int /*<<< orphan*/  ppt_tnt_64 ; 
 int /*<<< orphan*/  ppt_tsc ; 
 int /*<<< orphan*/  ppt_vmcs ; 
 int /*<<< orphan*/  pt_decode_cbr ; 
 int /*<<< orphan*/  pt_decode_cyc ; 
 int /*<<< orphan*/  pt_decode_exstop ; 
 int /*<<< orphan*/  pt_decode_fup ; 
 int /*<<< orphan*/  pt_decode_mnt ; 
 int /*<<< orphan*/  pt_decode_mtc ; 
 int /*<<< orphan*/  pt_decode_mwait ; 
 int /*<<< orphan*/  pt_decode_ovf ; 
 int /*<<< orphan*/  pt_decode_pad ; 
 int /*<<< orphan*/  pt_decode_pip ; 
 int /*<<< orphan*/  pt_decode_psb ; 
 int /*<<< orphan*/  pt_decode_psbend ; 
 int /*<<< orphan*/  pt_decode_ptw ; 
 int /*<<< orphan*/  pt_decode_pwre ; 
 int /*<<< orphan*/  pt_decode_pwrx ; 
 int /*<<< orphan*/  pt_decode_stop ; 
 int /*<<< orphan*/  pt_decode_tip ; 
 int /*<<< orphan*/  pt_decode_tip_pgd ; 
 int /*<<< orphan*/  pt_decode_tip_pge ; 
 int /*<<< orphan*/  pt_decode_tma ; 
 int /*<<< orphan*/  pt_decode_tnt_64 ; 
 int /*<<< orphan*/  pt_decode_tsc ; 
 int /*<<< orphan*/  pt_decode_vmcs ; 
 int /*<<< orphan*/  ptu_run_f (struct ptunit_suite,int /*<<< orphan*/ ,struct fetch_fixture) ; 
 int /*<<< orphan*/  ptu_run_fp (struct ptunit_suite,int /*<<< orphan*/ ,struct fetch_fixture,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ptunit_suite ptunit_mk_suite (int,char**) ; 
 int ptunit_report (struct ptunit_suite*) ; 

int main(int argc, char **argv)
{
	struct fetch_fixture ffix;
	struct ptunit_suite suite;

	ffix.init = ffix_init;
	ffix.fini = ffix_fini;

	suite = ptunit_mk_suite(argc, argv);

	ptu_run_f(suite, fetch_null, ffix);
	ptu_run_f(suite, fetch_empty, ffix);

	ptu_run_f(suite, fetch_unknown, ffix);
	ptu_run_f(suite, fetch_unknown_ext, ffix);
	ptu_run_f(suite, fetch_unknown_ext2, ffix);

	ptu_run_fp(suite, fetch_type, ffix, ppt_pad, &pt_decode_pad);
	ptu_run_fp(suite, fetch_type, ffix, ppt_psb, &pt_decode_psb);
	ptu_run_fp(suite, fetch_type, ffix, ppt_tip, &pt_decode_tip);
	ptu_run_fp(suite, fetch_type, ffix, ppt_tnt_64, &pt_decode_tnt_64);
	ptu_run_fp(suite, fetch_type, ffix, ppt_tip_pge, &pt_decode_tip_pge);
	ptu_run_fp(suite, fetch_type, ffix, ppt_tip_pgd, &pt_decode_tip_pgd);
	ptu_run_fp(suite, fetch_type, ffix, ppt_fup, &pt_decode_fup);
	ptu_run_fp(suite, fetch_type, ffix, ppt_pip, &pt_decode_pip);
	ptu_run_fp(suite, fetch_type, ffix, ppt_ovf, &pt_decode_ovf);
	ptu_run_fp(suite, fetch_type, ffix, ppt_psbend, &pt_decode_psbend);
	ptu_run_fp(suite, fetch_type, ffix, ppt_tsc, &pt_decode_tsc);
	ptu_run_fp(suite, fetch_type, ffix, ppt_cbr, &pt_decode_cbr);
	ptu_run_fp(suite, fetch_type, ffix, ppt_tma, &pt_decode_tma);
	ptu_run_fp(suite, fetch_type, ffix, ppt_mtc, &pt_decode_mtc);
	ptu_run_fp(suite, fetch_type, ffix, ppt_cyc, &pt_decode_cyc);
	ptu_run_fp(suite, fetch_type, ffix, ppt_stop, &pt_decode_stop);
	ptu_run_fp(suite, fetch_type, ffix, ppt_vmcs, &pt_decode_vmcs);
	ptu_run_fp(suite, fetch_type, ffix, ppt_mnt, &pt_decode_mnt);
	ptu_run_fp(suite, fetch_type, ffix, ppt_exstop, &pt_decode_exstop);
	ptu_run_fp(suite, fetch_type, ffix, ppt_mwait, &pt_decode_mwait);
	ptu_run_fp(suite, fetch_type, ffix, ppt_pwre, &pt_decode_pwre);
	ptu_run_fp(suite, fetch_type, ffix, ppt_pwrx, &pt_decode_pwrx);
	ptu_run_fp(suite, fetch_type, ffix, ppt_ptw, &pt_decode_ptw);

	ptu_run_f(suite, fetch_tnt_8, ffix);
	ptu_run_f(suite, fetch_mode_exec, ffix);
	ptu_run_f(suite, fetch_mode_tsx, ffix);
	ptu_run_f(suite, fetch_exstop_ip, ffix);

	return ptunit_report(&suite);
}