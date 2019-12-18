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
struct cryptocap {int cc_flags; scalar_t__ cc_koperations; int /*<<< orphan*/ * cc_dev; } ;
struct cryptkop {int dummy; } ;

/* Variables and functions */
 int CRYPTOCAP_F_CLEANUP ; 
 int CRYPTOCAP_F_HARDWARE ; 
 int CRYPTOCAP_F_SOFTWARE ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_ASSERT () ; 
 struct cryptocap* crypto_drivers ; 
 int crypto_drivers_num ; 
 scalar_t__ kdriver_suitable (struct cryptocap*,struct cryptkop const*) ; 

__attribute__((used)) static struct cryptocap *
crypto_select_kdriver(const struct cryptkop *krp, int flags)
{
	struct cryptocap *cap, *best;
	int match, hid;

	CRYPTO_DRIVER_ASSERT();

	/*
	 * Look first for hardware crypto devices if permitted.
	 */
	if (flags & CRYPTOCAP_F_HARDWARE)
		match = CRYPTOCAP_F_HARDWARE;
	else
		match = CRYPTOCAP_F_SOFTWARE;
	best = NULL;
again:
	for (hid = 0; hid < crypto_drivers_num; hid++) {
		cap = &crypto_drivers[hid];
		/*
		 * If it's not initialized, is in the process of
		 * going away, or is not appropriate (hardware
		 * or software based on match), then skip.
		 */
		if (cap->cc_dev == NULL ||
		    (cap->cc_flags & CRYPTOCAP_F_CLEANUP) ||
		    (cap->cc_flags & match) == 0)
			continue;

		/* verify all the algorithms are supported. */
		if (kdriver_suitable(cap, krp)) {
			if (best == NULL ||
			    cap->cc_koperations < best->cc_koperations)
				best = cap;
		}
	}
	if (best != NULL)
		return best;
	if (match == CRYPTOCAP_F_HARDWARE && (flags & CRYPTOCAP_F_SOFTWARE)) {
		/* sort of an Algol 68-style for loop */
		match = CRYPTOCAP_F_SOFTWARE;
		goto again;
	}
	return best;
}