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
struct TYPE_5__ {uintptr_t sival_ptr; scalar_t__ sival_int; } ;
struct siginfo32 {uintptr_t si_addr; int /*<<< orphan*/  si_overrun; int /*<<< orphan*/  si_timerid; TYPE_1__ si_value; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
struct TYPE_6__ {scalar_t__ sival_int; scalar_t__ sival_ptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  si_overrun; int /*<<< orphan*/  si_timerid; TYPE_2__ si_value; scalar_t__ si_addr; int /*<<< orphan*/  si_status; int /*<<< orphan*/  si_uid; int /*<<< orphan*/  si_pid; int /*<<< orphan*/  si_code; int /*<<< orphan*/  si_errno; int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_3__ siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct siginfo32*,int) ; 

__attribute__((used)) static void
elf_convert_siginfo(struct siginfo32 *sid, siginfo_t *sis)
{

	bzero(sid, sizeof(*sid));
	sid->si_signo = sis->si_signo;
	sid->si_errno = sis->si_errno;
	sid->si_code = sis->si_code;
	sid->si_pid = sis->si_pid;
	sid->si_uid = sis->si_uid;
	sid->si_status = sis->si_status;
	sid->si_addr = (uintptr_t)sis->si_addr;
#if _BYTE_ORDER == _BIG_ENDIAN
	if (sis->si_value.sival_int == 0)
		sid->si_value.sival_ptr = (uintptr_t)sis->si_value.sival_ptr;
	else
#endif
		sid->si_value.sival_int = sis->si_value.sival_int;
	sid->si_timerid = sis->si_timerid;
	sid->si_overrun = sis->si_overrun;
}