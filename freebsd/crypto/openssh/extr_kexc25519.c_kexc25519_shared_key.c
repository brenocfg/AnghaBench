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

/* Variables and functions */
 int CURVE25519_SIZE ; 
 int SSH_ERR_KEY_INVALID_EC_VALUE ; 
 int /*<<< orphan*/  crypto_scalarmult_curve25519 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dump_digest (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  explicit_bzero (int /*<<< orphan*/ *,int) ; 
 int sshbuf_put_bignum2_bytes (struct sshbuf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 
 scalar_t__ timingsafe_bcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

int
kexc25519_shared_key(const u_char key[CURVE25519_SIZE],
    const u_char pub[CURVE25519_SIZE], struct sshbuf *out)
{
	u_char shared_key[CURVE25519_SIZE];
	int r;

	/* Check for all-zero public key */
	explicit_bzero(shared_key, CURVE25519_SIZE);
	if (timingsafe_bcmp(pub, shared_key, CURVE25519_SIZE) == 0)
		return SSH_ERR_KEY_INVALID_EC_VALUE;

	crypto_scalarmult_curve25519(shared_key, key, pub);
#ifdef DEBUG_KEXECDH
	dump_digest("shared secret", shared_key, CURVE25519_SIZE);
#endif
	sshbuf_reset(out);
	r = sshbuf_put_bignum2_bytes(out, shared_key, CURVE25519_SIZE);
	explicit_bzero(shared_key, CURVE25519_SIZE);
	return r;
}