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
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int PEEK_U16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SSHBUF_ABORT () ; 
 int /*<<< orphan*/  SSHBUF_DBG (char*) ; 
 size_t SSHBUF_MAX_BIGNUM ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_BIGNUM_TOO_LARGE ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_MESSAGE_INCOMPLETE ; 
 scalar_t__ sshbuf_consume (struct sshbuf*,int) ; 
 int sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/ * sshbuf_ptr (struct sshbuf*) ; 

int
sshbuf_get_bignum1(struct sshbuf *buf, BIGNUM *v)
{
	const u_char *d = sshbuf_ptr(buf);
	u_int16_t len_bits;
	size_t len_bytes;

	/* Length in bits */
	if (sshbuf_len(buf) < 2)
		return SSH_ERR_MESSAGE_INCOMPLETE;
	len_bits = PEEK_U16(d);
	len_bytes = (len_bits + 7) >> 3;
	if (len_bytes > SSHBUF_MAX_BIGNUM)
		return SSH_ERR_BIGNUM_TOO_LARGE;
	if (sshbuf_len(buf) < 2 + len_bytes)
		return SSH_ERR_MESSAGE_INCOMPLETE;
	if (v != NULL && BN_bin2bn(d + 2, len_bytes, v) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if (sshbuf_consume(buf, 2 + len_bytes) != 0) {
		SSHBUF_DBG(("SSH_ERR_INTERNAL_ERROR"));
		SSHBUF_ABORT();
		return SSH_ERR_INTERNAL_ERROR;
	}
	return 0;
}