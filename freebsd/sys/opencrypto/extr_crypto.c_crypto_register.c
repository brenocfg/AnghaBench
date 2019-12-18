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
typedef  int u_int16_t ;
struct cryptocap {int* cc_alg; int* cc_max_op_len; scalar_t__ cc_sessions; int /*<<< orphan*/  cc_dev; } ;

/* Variables and functions */
 int CRYPTO_ALGORITHM_MAX ; 
 int CRYPTO_ALGORITHM_MIN ; 
 int CRYPTO_ALG_FLAG_SUPPORTED ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 int EINVAL ; 
 scalar_t__ bootverbose ; 
 struct cryptocap* crypto_checkdriver (int) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 

int
crypto_register(u_int32_t driverid, int alg, u_int16_t maxoplen,
    u_int32_t flags)
{
	struct cryptocap *cap;
	int err;

	CRYPTO_DRIVER_LOCK();

	cap = crypto_checkdriver(driverid);
	/* NB: algorithms are in the range [1..max] */
	if (cap != NULL &&
	    (CRYPTO_ALGORITHM_MIN <= alg && alg <= CRYPTO_ALGORITHM_MAX)) {
		/*
		 * XXX Do some performance testing to determine placing.
		 * XXX We probably need an auxiliary data structure that
		 * XXX describes relative performances.
		 */

		cap->cc_alg[alg] = flags | CRYPTO_ALG_FLAG_SUPPORTED;
		cap->cc_max_op_len[alg] = maxoplen;
		if (bootverbose)
			printf("crypto: %s registers alg %u flags %u maxoplen %u\n"
				, device_get_nameunit(cap->cc_dev)
				, alg
				, flags
				, maxoplen
			);
		cap->cc_sessions = 0;		/* Unmark */
		err = 0;
	} else
		err = EINVAL;

	CRYPTO_DRIVER_UNLOCK();
	return err;
}