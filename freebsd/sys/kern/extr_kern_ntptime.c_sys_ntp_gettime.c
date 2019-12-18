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
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct ntptimeval {int /*<<< orphan*/  time_state; } ;
struct ntp_gettime_args {int /*<<< orphan*/  ntvp; } ;
typedef  int /*<<< orphan*/  ntv ;

/* Variables and functions */
 int /*<<< orphan*/  NTP_LOCK () ; 
 int /*<<< orphan*/  NTP_UNLOCK () ; 
 int copyout (struct ntptimeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ntptimeval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntp_gettime1 (struct ntptimeval*) ; 

int
sys_ntp_gettime(struct thread *td, struct ntp_gettime_args *uap)
{	
	struct ntptimeval ntv;

	memset(&ntv, 0, sizeof(ntv));

	NTP_LOCK();
	ntp_gettime1(&ntv);
	NTP_UNLOCK();

	td->td_retval[0] = ntv.time_state;
	return (copyout(&ntv, uap->ntvp, sizeof(ntv)));
}