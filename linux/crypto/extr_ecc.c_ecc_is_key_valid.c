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
typedef  int /*<<< orphan*/  u64 ;
struct ecc_curve {int dummy; } ;

/* Variables and functions */
 unsigned int ECC_DIGITS_TO_BYTES_SHIFT ; 
 int EINVAL ; 
 int __ecc_is_key_valid (struct ecc_curve const*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct ecc_curve* ecc_get_curve (unsigned int) ; 

int ecc_is_key_valid(unsigned int curve_id, unsigned int ndigits,
		     const u64 *private_key, unsigned int private_key_len)
{
	int nbytes;
	const struct ecc_curve *curve = ecc_get_curve(curve_id);

	nbytes = ndigits << ECC_DIGITS_TO_BYTES_SHIFT;

	if (private_key_len != nbytes)
		return -EINVAL;

	return __ecc_is_key_valid(curve, private_key, ndigits);
}