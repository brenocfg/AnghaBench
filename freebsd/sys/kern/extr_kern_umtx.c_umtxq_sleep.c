#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct umtxq_chain {int /*<<< orphan*/  uc_lock; } ;
struct umtx_q {int uq_flags; int /*<<< orphan*/  uq_key; } ;
struct abs_timeout {scalar_t__ is_abs_real; } ;
struct TYPE_2__ {void* td_rtcgen; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int ETIMEDOUT ; 
 int PCATCH ; 
 int PDROP ; 
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (struct umtxq_chain*) ; 
 int UQF_UMTXQ ; 
 int abs_timeout_gethz (struct abs_timeout*) ; 
 int /*<<< orphan*/  abs_timeout_update (struct abs_timeout*) ; 
 void* atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 TYPE_1__* curthread ; 
 int msleep (struct umtx_q*,int /*<<< orphan*/ *,int,char const*,int) ; 
 int /*<<< orphan*/  rtc_generation ; 
 struct umtxq_chain* umtxq_getchain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
umtxq_sleep(struct umtx_q *uq, const char *wmesg, struct abs_timeout *abstime)
{
	struct umtxq_chain *uc;
	int error, timo;

	if (abstime != NULL && abstime->is_abs_real) {
		curthread->td_rtcgen = atomic_load_acq_int(&rtc_generation);
		abs_timeout_update(abstime);
	}

	uc = umtxq_getchain(&uq->uq_key);
	UMTXQ_LOCKED_ASSERT(uc);
	for (;;) {
		if (!(uq->uq_flags & UQF_UMTXQ)) {
			error = 0;
			break;
		}
		if (abstime != NULL) {
			timo = abs_timeout_gethz(abstime);
			if (timo < 0) {
				error = ETIMEDOUT;
				break;
			}
		} else
			timo = 0;
		error = msleep(uq, &uc->uc_lock, PCATCH | PDROP, wmesg, timo);
		if (error == EINTR || error == ERESTART) {
			umtxq_lock(&uq->uq_key);
			break;
		}
		if (abstime != NULL) {
			if (abstime->is_abs_real)
				curthread->td_rtcgen =
				    atomic_load_acq_int(&rtc_generation);
			abs_timeout_update(abstime);
		}
		umtxq_lock(&uq->uq_key);
	}

	curthread->td_rtcgen = 0;
	return (error);
}