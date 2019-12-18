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
typedef  int u_int32_t ;
struct cryptocap {int* cc_kalg; int /*<<< orphan*/  cc_dev; } ;

/* Variables and functions */
 int CRK_ALGORITHM_MAX ; 
 int CRK_ALGORITM_MIN ; 
 int CRYPTO_ALG_FLAG_SUPPORTED ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 int EINVAL ; 
 scalar_t__ bootverbose ; 
 struct cryptocap* crypto_checkdriver (int) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

int
crypto_kregister(u_int32_t driverid, int kalg, u_int32_t flags)
{
	struct cryptocap *cap;
	int err;

	CRYPTO_DRIVER_LOCK();

	cap = crypto_checkdriver(driverid);
	if (cap != NULL &&
	    (CRK_ALGORITM_MIN <= kalg && kalg <= CRK_ALGORITHM_MAX)) {
		/*
		 * XXX Do some performance testing to determine placing.
		 * XXX We probably need an auxiliary data structure that
		 * XXX describes relative performances.
		 */

		cap->cc_kalg[kalg] = flags | CRYPTO_ALG_FLAG_SUPPORTED;
		if (bootverbose)
			printf("crypto: %s registers key alg %u flags %u\n"
				, device_get_nameunit(cap->cc_dev)
				, kalg
				, flags
			);
		err = 0;
	} else
		err = EINVAL;

	CRYPTO_DRIVER_UNLOCK();
	return err;
}