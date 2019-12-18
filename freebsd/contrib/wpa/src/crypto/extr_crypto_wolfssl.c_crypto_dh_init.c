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
typedef  int /*<<< orphan*/  WC_RNG ;
typedef  int /*<<< orphan*/  DhKey ;

/* Variables and functions */
 scalar_t__ TEST_FAIL () ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ wc_DhGenerateKeyPair (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ wc_DhSetKey (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wc_FreeDhKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_FreeRng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wc_InitDhKey (int /*<<< orphan*/ *) ; 
 scalar_t__ wc_InitRng (int /*<<< orphan*/ *) ; 

int crypto_dh_init(u8 generator, const u8 *prime, size_t prime_len, u8 *privkey,
		   u8 *pubkey)
{
	int ret = -1;
	WC_RNG rng;
	DhKey *dh = NULL;
	word32 priv_sz, pub_sz;

	if (TEST_FAIL())
		return -1;

	dh = os_malloc(sizeof(DhKey));
	if (!dh)
		return -1;
	wc_InitDhKey(dh);

	if (wc_InitRng(&rng) != 0) {
		os_free(dh);
		return -1;
	}

	if (wc_DhSetKey(dh, prime, prime_len, &generator, 1) != 0)
		goto done;

	if (wc_DhGenerateKeyPair(dh, &rng, privkey, &priv_sz, pubkey, &pub_sz)
	    != 0)
		goto done;

	if (priv_sz < prime_len) {
		size_t pad_sz = prime_len - priv_sz;

		os_memmove(privkey + pad_sz, privkey, priv_sz);
		os_memset(privkey, 0, pad_sz);
	}

	if (pub_sz < prime_len) {
		size_t pad_sz = prime_len - pub_sz;

		os_memmove(pubkey + pad_sz, pubkey, pub_sz);
		os_memset(pubkey, 0, pad_sz);
	}
	ret = 0;
done:
	wc_FreeDhKey(dh);
	os_free(dh);
	wc_FreeRng(&rng);
	return ret;
}