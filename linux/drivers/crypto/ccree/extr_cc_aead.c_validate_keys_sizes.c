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
struct device {int dummy; } ;
struct cc_aead_ctx {int enc_keylen; int auth_keylen; int auth_mode; scalar_t__ flow_mode; int /*<<< orphan*/  drvdata; } ;

/* Variables and functions */
 int AES_KEYSIZE_128 ; 
 int AES_KEYSIZE_192 ; 
 int AES_KEYSIZE_256 ; 
 int DES3_EDE_KEY_SIZE ; 
#define  DRV_HASH_NULL 131 
#define  DRV_HASH_SHA1 130 
#define  DRV_HASH_SHA256 129 
#define  DRV_HASH_XCBC_MAC 128 
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ S_DIN_to_DES ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* drvdata_to_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_keys_sizes(struct cc_aead_ctx *ctx)
{
	struct device *dev = drvdata_to_dev(ctx->drvdata);

	dev_dbg(dev, "enc_keylen=%u  authkeylen=%u\n",
		ctx->enc_keylen, ctx->auth_keylen);

	switch (ctx->auth_mode) {
	case DRV_HASH_SHA1:
	case DRV_HASH_SHA256:
		break;
	case DRV_HASH_XCBC_MAC:
		if (ctx->auth_keylen != AES_KEYSIZE_128 &&
		    ctx->auth_keylen != AES_KEYSIZE_192 &&
		    ctx->auth_keylen != AES_KEYSIZE_256)
			return -ENOTSUPP;
		break;
	case DRV_HASH_NULL: /* Not authenc (e.g., CCM) - no auth_key) */
		if (ctx->auth_keylen > 0)
			return -EINVAL;
		break;
	default:
		dev_err(dev, "Invalid auth_mode=%d\n", ctx->auth_mode);
		return -EINVAL;
	}
	/* Check cipher key size */
	if (ctx->flow_mode == S_DIN_to_DES) {
		if (ctx->enc_keylen != DES3_EDE_KEY_SIZE) {
			dev_err(dev, "Invalid cipher(3DES) key size: %u\n",
				ctx->enc_keylen);
			return -EINVAL;
		}
	} else { /* Default assumed to be AES ciphers */
		if (ctx->enc_keylen != AES_KEYSIZE_128 &&
		    ctx->enc_keylen != AES_KEYSIZE_192 &&
		    ctx->enc_keylen != AES_KEYSIZE_256) {
			dev_err(dev, "Invalid cipher(AES) key size: %u\n",
				ctx->enc_keylen);
			return -EINVAL;
		}
	}

	return 0; /* All tests of keys sizes passed */
}