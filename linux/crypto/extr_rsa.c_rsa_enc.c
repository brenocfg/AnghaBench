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
struct rsa_mpi_key {int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct crypto_akcipher {int dummy; } ;
struct akcipher_request {int /*<<< orphan*/  dst_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  MPI ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int _rsa_enc (struct rsa_mpi_key const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  mpi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_read_raw_from_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mpi_write_to_sgl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct rsa_mpi_key* rsa_get_key (struct crypto_akcipher*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rsa_enc(struct akcipher_request *req)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	const struct rsa_mpi_key *pkey = rsa_get_key(tfm);
	MPI m, c = mpi_alloc(0);
	int ret = 0;
	int sign;

	if (!c)
		return -ENOMEM;

	if (unlikely(!pkey->n || !pkey->e)) {
		ret = -EINVAL;
		goto err_free_c;
	}

	ret = -ENOMEM;
	m = mpi_read_raw_from_sgl(req->src, req->src_len);
	if (!m)
		goto err_free_c;

	ret = _rsa_enc(pkey, c, m);
	if (ret)
		goto err_free_m;

	ret = mpi_write_to_sgl(c, req->dst, req->dst_len, &sign);
	if (ret)
		goto err_free_m;

	if (sign < 0)
		ret = -EBADMSG;

err_free_m:
	mpi_free(m);
err_free_c:
	mpi_free(c);
	return ret;
}