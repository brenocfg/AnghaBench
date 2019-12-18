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
struct rsa_key {size_t n_sz; void const* n; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ fips_enabled ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int rsa_get_n(void *context, size_t hdrlen, unsigned char tag,
	      const void *value, size_t vlen)
{
	struct rsa_key *key = context;
	const u8 *ptr = value;
	size_t n_sz = vlen;

	/* invalid key provided */
	if (!value || !vlen)
		return -EINVAL;

	if (fips_enabled) {
		while (n_sz && !*ptr) {
			ptr++;
			n_sz--;
		}

		/* In FIPS mode only allow key size 2K and higher */
		if (n_sz < 256) {
			pr_err("RSA: key size not allowed in FIPS mode\n");
			return -EINVAL;
		}
	}

	key->n = value;
	key->n_sz = vlen;

	return 0;
}