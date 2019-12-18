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
typedef  int u_char ;
struct sshbuf {int dummy; } ;
typedef  int /*<<< orphan*/  d ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_bn2bin (int /*<<< orphan*/  const*,int*) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 int SSHBUF_MAX_BIGNUM ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  explicit_bzero (int*,int) ; 
 int sshbuf_put_string (struct sshbuf*,int*,int) ; 

int
sshbuf_put_bignum2(struct sshbuf *buf, const BIGNUM *v)
{
	u_char d[SSHBUF_MAX_BIGNUM + 1];
	int len = BN_num_bytes(v), prepend = 0, r;

	if (len < 0 || len > SSHBUF_MAX_BIGNUM)
		return SSH_ERR_INVALID_ARGUMENT;
	*d = '\0';
	if (BN_bn2bin(v, d + 1) != len)
		return SSH_ERR_INTERNAL_ERROR; /* Shouldn't happen */
	/* If MSB is set, prepend a \0 */
	if (len > 0 && (d[1] & 0x80) != 0)
		prepend = 1;
	if ((r = sshbuf_put_string(buf, d + 1 - prepend, len + prepend)) < 0) {
		explicit_bzero(d, sizeof(d));
		return r;
	}
	explicit_bzero(d, sizeof(d));
	return 0;
}