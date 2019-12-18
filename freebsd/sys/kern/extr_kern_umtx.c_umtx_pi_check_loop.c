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
struct umtx_pi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtx_lock ; 
 struct umtx_pi* umtx_pi_next (struct umtx_pi*) ; 

__attribute__((used)) static bool
umtx_pi_check_loop(struct umtx_pi *pi)
{
	struct umtx_pi *pi1;	/* fast iterator */

	mtx_assert(&umtx_lock, MA_OWNED);
	if (pi == NULL)
		return (false);
	pi1 = pi;
	for (;;) {
		pi = umtx_pi_next(pi);
		if (pi == NULL)
			break;
		pi1 = umtx_pi_next(pi1);
		if (pi1 == NULL)
			break;
		pi1 = umtx_pi_next(pi1);
		if (pi1 == NULL)
			break;
		if (pi == pi1)
			return (true);
	}
	return (false);
}