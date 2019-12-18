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
struct rsa_mpi_key {void* n; void* e; void* d; } ;
struct rsa_key {int /*<<< orphan*/  n_sz; int /*<<< orphan*/  n; int /*<<< orphan*/  e_sz; int /*<<< orphan*/  e; int /*<<< orphan*/  d_sz; int /*<<< orphan*/  d; int /*<<< orphan*/  member_0; } ;
struct crypto_akcipher {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct rsa_mpi_key* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int mpi_get_size (void*) ; 
 void* mpi_read_raw_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rsa_check_key_length (int) ; 
 int /*<<< orphan*/  rsa_free_mpi_key (struct rsa_mpi_key*) ; 
 int rsa_parse_priv_key (struct rsa_key*,void const*,unsigned int) ; 

__attribute__((used)) static int rsa_set_priv_key(struct crypto_akcipher *tfm, const void *key,
			    unsigned int keylen)
{
	struct rsa_mpi_key *mpi_key = akcipher_tfm_ctx(tfm);
	struct rsa_key raw_key = {0};
	int ret;

	/* Free the old MPI key if any */
	rsa_free_mpi_key(mpi_key);

	ret = rsa_parse_priv_key(&raw_key, key, keylen);
	if (ret)
		return ret;

	mpi_key->d = mpi_read_raw_data(raw_key.d, raw_key.d_sz);
	if (!mpi_key->d)
		goto err;

	mpi_key->e = mpi_read_raw_data(raw_key.e, raw_key.e_sz);
	if (!mpi_key->e)
		goto err;

	mpi_key->n = mpi_read_raw_data(raw_key.n, raw_key.n_sz);
	if (!mpi_key->n)
		goto err;

	if (rsa_check_key_length(mpi_get_size(mpi_key->n) << 3)) {
		rsa_free_mpi_key(mpi_key);
		return -EINVAL;
	}

	return 0;

err:
	rsa_free_mpi_key(mpi_key);
	return -ENOMEM;
}