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
typedef  size_t word32 ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  DhKey ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 scalar_t__ wc_DhAgree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 scalar_t__ wc_DhSetKey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wc_FreeDhKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_InitDhKey (int /*<<< orphan*/ *) ; 

int crypto_dh_derive_secret(u8 generator, const u8 *prime, size_t prime_len,
			    const u8 *order, size_t order_len,
			    const u8 *privkey, size_t privkey_len,
			    const u8 *pubkey, size_t pubkey_len,
			    u8 *secret, size_t *len)
{
	int ret = -1;
	DhKey *dh;
	word32 secret_sz;

	dh = os_malloc(sizeof(DhKey));
	if (!dh)
		return -1;
	wc_InitDhKey(dh);

	if (wc_DhSetKey(dh, prime, prime_len, &generator, 1) != 0)
		goto done;

	if (wc_DhAgree(dh, secret, &secret_sz, privkey, privkey_len, pubkey,
		       pubkey_len) != 0)
		goto done;

	*len = secret_sz;
	ret = 0;
done:
	wc_FreeDhKey(dh);
	os_free(dh);
	return ret;
}