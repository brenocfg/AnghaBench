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
typedef  int /*<<< orphan*/ * gcry_mpi_t ;

/* Variables and functions */
 int /*<<< orphan*/  GCRYMPI_FMT_USG ; 
 scalar_t__ GPG_ERR_NO_ERROR ; 
 int crypto_mod_exp (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ gcry_mpi_cmp_ui (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * gcry_mpi_new (size_t) ; 
 int /*<<< orphan*/  gcry_mpi_powm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcry_mpi_release (int /*<<< orphan*/ *) ; 
 scalar_t__ gcry_mpi_scan (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

int crypto_dh_derive_secret(u8 generator, const u8 *prime, size_t prime_len,
			    const u8 *order, size_t order_len,
			    const u8 *privkey, size_t privkey_len,
			    const u8 *pubkey, size_t pubkey_len,
			    u8 *secret, size_t *len)
{
	gcry_mpi_t pub = NULL;
	int res = -1;

	if (pubkey_len > prime_len ||
	    (pubkey_len == prime_len &&
	     os_memcmp(pubkey, prime, prime_len) >= 0))
		return -1;

	if (gcry_mpi_scan(&pub, GCRYMPI_FMT_USG, pubkey, pubkey_len, NULL) !=
	    GPG_ERR_NO_ERROR ||
	    gcry_mpi_cmp_ui(pub, 1) <= 0)
		goto fail;

	if (order) {
		gcry_mpi_t p = NULL, q = NULL, tmp;
		int failed;

		/* verify: pubkey^q == 1 mod p */
		tmp = gcry_mpi_new(prime_len * 8);
		failed = !tmp ||
			gcry_mpi_scan(&p, GCRYMPI_FMT_USG, prime, prime_len,
				      NULL) != GPG_ERR_NO_ERROR ||
			gcry_mpi_scan(&q, GCRYMPI_FMT_USG, order, order_len,
				      NULL) != GPG_ERR_NO_ERROR;
		if (!failed) {
			gcry_mpi_powm(tmp, pub, q, p);
			failed = gcry_mpi_cmp_ui(tmp, 1) != 0;
		}
		gcry_mpi_release(p);
		gcry_mpi_release(q);
		gcry_mpi_release(tmp);
		if (failed)
			goto fail;
	}

	res = crypto_mod_exp(pubkey, pubkey_len, privkey, privkey_len,
			     prime, prime_len, secret, len);
fail:
	gcry_mpi_release(pub);
	return res;
}