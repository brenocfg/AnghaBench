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
typedef  int /*<<< orphan*/  u8 ;
struct rtattr {scalar_t__ rta_type; scalar_t__ rta_len; } ;
struct crypto_authenc_keys {unsigned int enckeylen; int authkeylen; int /*<<< orphan*/  const* enckey; int /*<<< orphan*/  const* authkey; } ;
struct crypto_authenc_key_param {int /*<<< orphan*/  enckeylen; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ CRYPTO_AUTHENC_KEYA_PARAM ; 
 int EINVAL ; 
 int RTA_ALIGNTO ; 
 struct crypto_authenc_key_param* RTA_DATA (struct rtattr*) ; 
 int /*<<< orphan*/  RTA_OK (struct rtattr*,unsigned int) ; 
 int RTA_PAYLOAD (struct rtattr*) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 

int crypto_authenc_extractkeys(struct crypto_authenc_keys *keys, const u8 *key,
			       unsigned int keylen)
{
	struct rtattr *rta = (struct rtattr *)key;
	struct crypto_authenc_key_param *param;

	if (!RTA_OK(rta, keylen))
		return -EINVAL;
	if (rta->rta_type != CRYPTO_AUTHENC_KEYA_PARAM)
		return -EINVAL;

	/*
	 * RTA_OK() didn't align the rtattr's payload when validating that it
	 * fits in the buffer.  Yet, the keys should start on the next 4-byte
	 * aligned boundary.  To avoid confusion, require that the rtattr
	 * payload be exactly the param struct, which has a 4-byte aligned size.
	 */
	if (RTA_PAYLOAD(rta) != sizeof(*param))
		return -EINVAL;
	BUILD_BUG_ON(sizeof(*param) % RTA_ALIGNTO);

	param = RTA_DATA(rta);
	keys->enckeylen = be32_to_cpu(param->enckeylen);

	key += rta->rta_len;
	keylen -= rta->rta_len;

	if (keylen < keys->enckeylen)
		return -EINVAL;

	keys->authkeylen = keylen - keys->enckeylen;
	keys->authkey = key;
	keys->enckey = key + keys->authkeylen;

	return 0;
}