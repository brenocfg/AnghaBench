#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sival_int; } ;
struct siginfo32 {uintptr_t si_addr; int /*<<< orphan*/  si_overrun; int /*<<< orphan*/  si_timerid; TYPE_1__ si_value; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
struct TYPE_6__ {int /*<<< orphan*/  sival_int; } ;
struct TYPE_7__ {int /*<<< orphan*/  si_overrun; int /*<<< orphan*/  si_timerid; TYPE_2__ si_value; scalar_t__ si_addr; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_3__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct siginfo32*,int) ; 

void
siginfo_to_siginfo32(const siginfo_t *src, struct siginfo32 *dst)
{
	bzero(dst, sizeof(*dst));
	dst->si_signo = src->si_signo;
	dst->si_errno = src->si_errno;
	dst->si_code = src->si_code;
	dst->si_pid = src->si_pid;
	dst->si_uid = src->si_uid;
	dst->si_status = src->si_status;
	dst->si_addr = (uintptr_t)src->si_addr;
	dst->si_value.sival_int = src->si_value.sival_int;
	dst->si_timerid = src->si_timerid;
	dst->si_overrun = src->si_overrun;
}