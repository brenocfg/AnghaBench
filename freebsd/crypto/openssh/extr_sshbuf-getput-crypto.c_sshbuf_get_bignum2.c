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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int sshbuf_get_bignum2_bytes_direct (struct sshbuf*,int /*<<< orphan*/  const**,size_t*) ; 

int
sshbuf_get_bignum2(struct sshbuf *buf, BIGNUM *v)
{
	const u_char *d;
	size_t len;
	int r;

	if ((r = sshbuf_get_bignum2_bytes_direct(buf, &d, &len)) != 0)
		return r;
	if (v != NULL && BN_bin2bn(d, len, v) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	return 0;
}