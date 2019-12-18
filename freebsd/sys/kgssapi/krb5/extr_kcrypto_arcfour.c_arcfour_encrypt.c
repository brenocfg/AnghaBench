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
typedef  int /*<<< orphan*/  uint8_t ;
struct rc4_state {int dummy; } ;
struct mbuf {int dummy; } ;
struct krb5_key_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  arcfour_derive_key (struct krb5_key_state const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arcfour_hmac (int /*<<< orphan*/ *,void*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_apply (struct mbuf*,size_t,size_t,int /*<<< orphan*/ ,struct rc4_state*) ; 
 int /*<<< orphan*/  rc4_crypt_int ; 
 int /*<<< orphan*/  rc4_init (struct rc4_state*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
arcfour_encrypt(const struct krb5_key_state *ks, struct mbuf *inout,
    size_t skip, size_t len, void *ivec, size_t ivlen)
{
	struct rc4_state rs;
	uint8_t newkey[16];

	arcfour_derive_key(ks, 0, newkey);

	/*
	 * If we have an IV, then generate a new key from it using HMAC.
	 */
	if (ivec) {
		uint8_t kk[16];
		arcfour_hmac(newkey, ivec, ivlen, kk);
		rc4_init(&rs, kk, 16);
	} else {
		rc4_init(&rs, newkey, 16);
	}

	m_apply(inout, skip, len, rc4_crypt_int, &rs);
}