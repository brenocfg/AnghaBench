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
typedef  int /*<<< orphan*/  d ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_bn2bin (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  POKE_U16 (int /*<<< orphan*/ *,int) ; 
 int SSHBUF_MAX_BIGNUM ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int sshbuf_reserve (struct sshbuf*,size_t,int /*<<< orphan*/ **) ; 

int
sshbuf_put_bignum1(struct sshbuf *buf, const BIGNUM *v)
{
	int r, len_bits = BN_num_bits(v);
	size_t len_bytes = (len_bits + 7) / 8;
	u_char d[SSHBUF_MAX_BIGNUM], *dp;

	if (len_bits < 0 || len_bytes > SSHBUF_MAX_BIGNUM)
		return SSH_ERR_INVALID_ARGUMENT;
	if (BN_bn2bin(v, d) != (int)len_bytes)
		return SSH_ERR_INTERNAL_ERROR; /* Shouldn't happen */
	if ((r = sshbuf_reserve(buf, len_bytes + 2, &dp)) < 0) {
		explicit_bzero(d, sizeof(d));
		return r;
	}
	POKE_U16(dp, len_bits);
	if (len_bytes != 0)
		memcpy(dp + 2, d, len_bytes);
	explicit_bzero(d, sizeof(d));
	return 0;
}