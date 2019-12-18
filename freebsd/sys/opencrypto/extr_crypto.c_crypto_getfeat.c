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
struct cryptocap {int cc_flags; int* cc_kalg; } ;

/* Variables and functions */
 int CRK_ALGORITHM_MAX ; 
 int CRYPTOCAP_F_SOFTWARE ; 
 int CRYPTO_ALG_FLAG_SUPPORTED ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 int /*<<< orphan*/  crypto_devallowsoft ; 
 struct cryptocap* crypto_drivers ; 
 int crypto_drivers_num ; 

int
crypto_getfeat(int *featp)
{
	int hid, kalg, feat = 0;

	CRYPTO_DRIVER_LOCK();
	for (hid = 0; hid < crypto_drivers_num; hid++) {
		const struct cryptocap *cap = &crypto_drivers[hid];

		if ((cap->cc_flags & CRYPTOCAP_F_SOFTWARE) &&
		    !crypto_devallowsoft) {
			continue;
		}
		for (kalg = 0; kalg < CRK_ALGORITHM_MAX; kalg++)
			if (cap->cc_kalg[kalg] & CRYPTO_ALG_FLAG_SUPPORTED)
				feat |=  1 << kalg;
	}
	CRYPTO_DRIVER_UNLOCK();
	*featp = feat;
	return (0);
}