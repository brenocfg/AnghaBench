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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 scalar_t__ MP_OKAY ; 
 scalar_t__ TEST_FAIL () ; 
 scalar_t__ crypto_bignum_init () ; 
 scalar_t__ mp_read_unsigned_bin (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 

struct crypto_bignum * crypto_bignum_init_set(const u8 *buf, size_t len)
{
	mp_int *a;

	if (TEST_FAIL())
		return NULL;

	a = (mp_int *) crypto_bignum_init();
	if (!a)
		return NULL;

	if (mp_read_unsigned_bin(a, buf, len) != MP_OKAY) {
		os_free(a);
		a = NULL;
	}

	return (struct crypto_bignum *) a;
}