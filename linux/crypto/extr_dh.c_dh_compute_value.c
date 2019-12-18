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
struct kpp_request {scalar_t__ src; int /*<<< orphan*/  dst_len; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; } ;
struct dh_ctx {scalar_t__ g; int /*<<< orphan*/  xa; } ;
struct crypto_kpp {int dummy; } ;
typedef  scalar_t__ MPI ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int _compute_val (struct dh_ctx*,scalar_t__,scalar_t__) ; 
 struct crypto_kpp* crypto_kpp_reqtfm (struct kpp_request*) ; 
 struct dh_ctx* dh_get_ctx (struct crypto_kpp*) ; 
 int dh_is_pubkey_valid (struct dh_ctx*,scalar_t__) ; 
 scalar_t__ mpi_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_free (scalar_t__) ; 
 scalar_t__ mpi_read_raw_from_sgl (scalar_t__,int /*<<< orphan*/ ) ; 
 int mpi_write_to_sgl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dh_compute_value(struct kpp_request *req)
{
	struct crypto_kpp *tfm = crypto_kpp_reqtfm(req);
	struct dh_ctx *ctx = dh_get_ctx(tfm);
	MPI base, val = mpi_alloc(0);
	int ret = 0;
	int sign;

	if (!val)
		return -ENOMEM;

	if (unlikely(!ctx->xa)) {
		ret = -EINVAL;
		goto err_free_val;
	}

	if (req->src) {
		base = mpi_read_raw_from_sgl(req->src, req->src_len);
		if (!base) {
			ret = -EINVAL;
			goto err_free_val;
		}
		ret = dh_is_pubkey_valid(ctx, base);
		if (ret)
			goto err_free_base;
	} else {
		base = ctx->g;
	}

	ret = _compute_val(ctx, base, val);
	if (ret)
		goto err_free_base;

	ret = mpi_write_to_sgl(val, req->dst, req->dst_len, &sign);
	if (ret)
		goto err_free_base;

	if (sign < 0)
		ret = -EBADMSG;
err_free_base:
	if (req->src)
		mpi_free(base);
err_free_val:
	mpi_free(val);
	return ret;
}