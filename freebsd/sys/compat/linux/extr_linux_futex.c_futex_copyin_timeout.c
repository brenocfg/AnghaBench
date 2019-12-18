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
struct timespec {int dummy; } ;
struct l_timespec {int dummy; } ;
typedef  int /*<<< orphan*/  lts ;

/* Variables and functions */
 int LINUX_FUTEX_WAIT_BITSET ; 
 int copyin (struct l_timespec*,struct l_timespec*,int) ; 
 int linux_to_native_timespec (struct timespec*,struct l_timespec*) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 

__attribute__((used)) static int
futex_copyin_timeout(int op, struct l_timespec *luts, int clockrt,
    struct timespec *ts)
{
	struct l_timespec lts;
	struct timespec kts;
	int error;

	error = copyin(luts, &lts, sizeof(lts));
	if (error)
		return (error);

	error = linux_to_native_timespec(ts, &lts);
	if (error)
		return (error);
	if (clockrt) {
		nanotime(&kts);
		timespecsub(ts, &kts, ts);
	} else if (op == LINUX_FUTEX_WAIT_BITSET) {
		nanouptime(&kts);
		timespecsub(ts, &kts, ts);
	}
	return (error);
}