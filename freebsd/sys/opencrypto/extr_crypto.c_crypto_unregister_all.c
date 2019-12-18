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
typedef  int /*<<< orphan*/  u_int32_t ;
struct cryptocap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DRIVER_LOCK () ; 
 int /*<<< orphan*/  CRYPTO_DRIVER_UNLOCK () ; 
 int EINVAL ; 
 struct cryptocap* crypto_checkdriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  driver_finis (struct cryptocap*) ; 

int
crypto_unregister_all(u_int32_t driverid)
{
	struct cryptocap *cap;
	int err;

	CRYPTO_DRIVER_LOCK();
	cap = crypto_checkdriver(driverid);
	if (cap != NULL) {
		driver_finis(cap);
		err = 0;
	} else
		err = EINVAL;
	CRYPTO_DRIVER_UNLOCK();

	return err;
}