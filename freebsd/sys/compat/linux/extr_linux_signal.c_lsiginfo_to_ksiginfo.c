#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  lsi_int; int /*<<< orphan*/  lsi_addr; int /*<<< orphan*/  lsi_status; int /*<<< orphan*/  lsi_uid; int /*<<< orphan*/  lsi_pid; int /*<<< orphan*/  lsi_code; } ;
typedef  TYPE_3__ l_siginfo_t ;
struct TYPE_7__ {int /*<<< orphan*/  sival_int; } ;
struct TYPE_8__ {TYPE_1__ si_value; } ;
struct TYPE_10__ {int ksi_signo; TYPE_2__ ksi_info; int /*<<< orphan*/  ksi_addr; int /*<<< orphan*/  ksi_status; int /*<<< orphan*/  ksi_uid; int /*<<< orphan*/  ksi_pid; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_4__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 

void
lsiginfo_to_ksiginfo(const l_siginfo_t *lsi, ksiginfo_t *ksi, int sig)
{

	ksi->ksi_signo = sig;
	ksi->ksi_code = lsi->lsi_code;	/* XXX. Convert. */
	ksi->ksi_pid = lsi->lsi_pid;
	ksi->ksi_uid = lsi->lsi_uid;
	ksi->ksi_status = lsi->lsi_status;
	ksi->ksi_addr = PTRIN(lsi->lsi_addr);
	ksi->ksi_info.si_value.sival_int = lsi->lsi_int;
}