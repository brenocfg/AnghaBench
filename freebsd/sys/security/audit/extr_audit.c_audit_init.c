#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kaudit_record {int dummy; } ;
struct TYPE_10__ {scalar_t__ af_currsz; scalar_t__ af_filesz; } ;
struct TYPE_6__ {int /*<<< orphan*/ * at_addr; int /*<<< orphan*/  at_type; } ;
struct TYPE_9__ {TYPE_1__ ai_termid; } ;
struct TYPE_8__ {scalar_t__ am_failure; scalar_t__ am_success; } ;
struct TYPE_7__ {int /*<<< orphan*/  aq_minfree; int /*<<< orphan*/  aq_bufsz; int /*<<< orphan*/  aq_lowater; int /*<<< orphan*/  aq_hiwater; } ;

/* Variables and functions */
 int /*<<< orphan*/  AQ_BUFSZ ; 
 int /*<<< orphan*/  AQ_HIWATER ; 
 int /*<<< orphan*/  AQ_LOWATER ; 
 int /*<<< orphan*/  AU_FS_MINFREE ; 
 int /*<<< orphan*/  AU_IPv4 ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  KINFO_LOCK_INIT () ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 scalar_t__ audit_arge ; 
 scalar_t__ audit_argv ; 
 int /*<<< orphan*/  audit_fail_cv ; 
 scalar_t__ audit_fail_stop ; 
 TYPE_5__ audit_fstat ; 
 scalar_t__ audit_in_failure ; 
 TYPE_4__ audit_kinfo ; 
 int /*<<< orphan*/  audit_mtx ; 
 TYPE_3__ audit_nae_mask ; 
 scalar_t__ audit_panic_on_write_fail ; 
 scalar_t__ audit_pre_q_len ; 
 int /*<<< orphan*/  audit_q ; 
 scalar_t__ audit_q_len ; 
 TYPE_2__ audit_qctrl ; 
 int /*<<< orphan*/  audit_record_ctor ; 
 int /*<<< orphan*/  audit_record_dtor ; 
 int /*<<< orphan*/  audit_record_zone ; 
 int /*<<< orphan*/  audit_shutdown ; 
 int audit_syscalls_enabled ; 
 int /*<<< orphan*/  audit_syscalls_enabled_update () ; 
 scalar_t__ audit_trail_enabled ; 
 scalar_t__ audit_trail_suspended ; 
 int /*<<< orphan*/  audit_trigger_init () ; 
 int /*<<< orphan*/  audit_watermark_cv ; 
 int /*<<< orphan*/  audit_worker_cv ; 
 int /*<<< orphan*/  audit_worker_init () ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kau_init () ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audit_init(void)
{

	audit_trail_enabled = 0;
	audit_trail_suspended = 0;
	audit_syscalls_enabled = false;
	audit_panic_on_write_fail = 0;
	audit_fail_stop = 0;
	audit_in_failure = 0;
	audit_argv = 0;
	audit_arge = 0;

	audit_fstat.af_filesz = 0;	/* '0' means unset, unbounded. */
	audit_fstat.af_currsz = 0;
	audit_nae_mask.am_success = 0;
	audit_nae_mask.am_failure = 0;

	TAILQ_INIT(&audit_q);
	audit_q_len = 0;
	audit_pre_q_len = 0;
	audit_qctrl.aq_hiwater = AQ_HIWATER;
	audit_qctrl.aq_lowater = AQ_LOWATER;
	audit_qctrl.aq_bufsz = AQ_BUFSZ;
	audit_qctrl.aq_minfree = AU_FS_MINFREE;

	audit_kinfo.ai_termid.at_type = AU_IPv4;
	audit_kinfo.ai_termid.at_addr[0] = INADDR_ANY;

	mtx_init(&audit_mtx, "audit_mtx", NULL, MTX_DEF);
	KINFO_LOCK_INIT();
	cv_init(&audit_worker_cv, "audit_worker_cv");
	cv_init(&audit_watermark_cv, "audit_watermark_cv");
	cv_init(&audit_fail_cv, "audit_fail_cv");

	audit_record_zone = uma_zcreate("audit_record",
	    sizeof(struct kaudit_record), audit_record_ctor,
	    audit_record_dtor, NULL, NULL, UMA_ALIGN_PTR, 0);

	/* First initialisation of audit_syscalls_enabled. */
	audit_syscalls_enabled_update();

	/* Initialize the BSM audit subsystem. */
	kau_init();

	audit_trigger_init();

	/* Register shutdown handler. */
	EVENTHANDLER_REGISTER(shutdown_pre_sync, audit_shutdown, NULL,
	    SHUTDOWN_PRI_FIRST);

	/* Start audit worker thread. */
	audit_worker_init();
}