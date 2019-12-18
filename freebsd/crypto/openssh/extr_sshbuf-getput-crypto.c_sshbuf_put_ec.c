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
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 size_t EC_POINT_point2oct (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POINT_CONVERSION_UNCOMPRESSED ; 
 int SSHBUF_MAX_ECPOINT ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,size_t) ; 
 int sshbuf_put_string (struct sshbuf*,int /*<<< orphan*/ *,size_t) ; 

int
sshbuf_put_ec(struct sshbuf *buf, const EC_POINT *v, const EC_GROUP *g)
{
	u_char d[SSHBUF_MAX_ECPOINT];
	BN_CTX *bn_ctx;
	size_t len;
	int ret;

	if ((bn_ctx = BN_CTX_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((len = EC_POINT_point2oct(g, v, POINT_CONVERSION_UNCOMPRESSED,
	    NULL, 0, bn_ctx)) > SSHBUF_MAX_ECPOINT) {
		BN_CTX_free(bn_ctx);
		return SSH_ERR_INVALID_ARGUMENT;
	}
	if (EC_POINT_point2oct(g, v, POINT_CONVERSION_UNCOMPRESSED,
	    d, len, bn_ctx) != len) {
		BN_CTX_free(bn_ctx);
		return SSH_ERR_INTERNAL_ERROR; /* Shouldn't happen */
	}
	BN_CTX_free(bn_ctx);
	ret = sshbuf_put_string(buf, d, len);
	explicit_bzero(d, len);
	return ret;
}