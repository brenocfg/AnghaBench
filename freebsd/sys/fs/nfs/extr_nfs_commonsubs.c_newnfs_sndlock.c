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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFSLOCKSOCK () ; 
 int NFSR_SNDLOCK ; 
 int NFSR_WANTSND ; 
 int /*<<< orphan*/  NFSSOCKMUTEXPTR ; 
 int /*<<< orphan*/  NFSUNLOCKSOCK () ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  nfsmsleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,struct timespec*) ; 

int
newnfs_sndlock(int *flagp)
{
	struct timespec ts;

	NFSLOCKSOCK();
	while (*flagp & NFSR_SNDLOCK) {
		*flagp |= NFSR_WANTSND;
		ts.tv_sec = 0;
		ts.tv_nsec = 0;
		(void) nfsmsleep((caddr_t)flagp, NFSSOCKMUTEXPTR,
		    PZERO - 1, "nfsndlck", &ts);
	}
	*flagp |= NFSR_SNDLOCK;
	NFSUNLOCKSOCK();
	return (0);
}