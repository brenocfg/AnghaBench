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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
struct ssh {int dummy; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int kex_derive_keys (struct ssh*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sshbuf*) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int sshbuf_put_bignum2 (struct sshbuf*,int /*<<< orphan*/  const*) ; 

int
kex_derive_keys_bn(struct ssh *ssh, u_char *hash, u_int hashlen,
    const BIGNUM *secret)
{
	struct sshbuf *shared_secret;
	int r;

	if ((shared_secret = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_put_bignum2(shared_secret, secret)) == 0)
		r = kex_derive_keys(ssh, hash, hashlen, shared_secret);
	sshbuf_free(shared_secret);
	return r;
}