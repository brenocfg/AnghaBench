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
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFSLOCKSOCK () ; 
 int NFSR_SNDLOCK ; 
 int NFSR_WANTSND ; 
 int /*<<< orphan*/  NFSUNLOCKSOCK () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

void
newnfs_sndunlock(int *flagp)
{

	NFSLOCKSOCK();
	if ((*flagp & NFSR_SNDLOCK) == 0)
		panic("nfs sndunlock");
	*flagp &= ~NFSR_SNDLOCK;
	if (*flagp & NFSR_WANTSND) {
		*flagp &= ~NFSR_WANTSND;
		wakeup((caddr_t)flagp);
	}
	NFSUNLOCKSOCK();
}