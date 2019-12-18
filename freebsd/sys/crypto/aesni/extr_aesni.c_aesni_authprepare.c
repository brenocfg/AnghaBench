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
struct aesni_session {scalar_t__ auth_algo; int /*<<< orphan*/  hmac_key; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_SHA1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int
aesni_authprepare(struct aesni_session *ses, int klen, const void *cri_key)
{
	int keylen;

	if (klen % 8 != 0)
		return (EINVAL);
	keylen = klen / 8;
	if (keylen > sizeof(ses->hmac_key))
		return (EINVAL);
	if (ses->auth_algo == CRYPTO_SHA1 && keylen > 0)
		return (EINVAL);
	memcpy(ses->hmac_key, cri_key, keylen);
	return (0);
}