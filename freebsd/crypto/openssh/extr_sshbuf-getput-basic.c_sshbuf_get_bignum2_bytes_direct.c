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

/* Variables and functions */
 int /*<<< orphan*/  SSHBUF_ABORT () ; 
 int /*<<< orphan*/  SSHBUF_DBG (char*) ; 
 int SSHBUF_MAX_BIGNUM ; 
 int SSH_ERR_BIGNUM_IS_NEGATIVE ; 
 int SSH_ERR_BIGNUM_TOO_LARGE ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 scalar_t__ sshbuf_consume (struct sshbuf*,size_t) ; 
 int sshbuf_peek_string_direct (struct sshbuf*,int const**,size_t*) ; 

int
sshbuf_get_bignum2_bytes_direct(struct sshbuf *buf,
    const u_char **valp, size_t *lenp)
{
	const u_char *d;
	size_t len, olen;
	int r;

	if ((r = sshbuf_peek_string_direct(buf, &d, &olen)) < 0)
		return r;
	len = olen;
	/* Refuse negative (MSB set) bignums */
	if ((len != 0 && (*d & 0x80) != 0))
		return SSH_ERR_BIGNUM_IS_NEGATIVE;
	/* Refuse overlong bignums, allow prepended \0 to avoid MSB set */
	if (len > SSHBUF_MAX_BIGNUM + 1 ||
	    (len == SSHBUF_MAX_BIGNUM + 1 && *d != 0))
		return SSH_ERR_BIGNUM_TOO_LARGE;
	/* Trim leading zeros */
	while (len > 0 && *d == 0x00) {
		d++;
		len--;
	}
	if (valp != NULL)
		*valp = d;
	if (lenp != NULL)
		*lenp = len;
	if (sshbuf_consume(buf, olen + 4) != 0) {
		/* Shouldn't happen */
		SSHBUF_DBG(("SSH_ERR_INTERNAL_ERROR"));
		SSHBUF_ABORT();
		return SSH_ERR_INTERNAL_ERROR;
	}
	return 0;
}