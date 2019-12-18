#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct aes_xts_ctx {int /*<<< orphan*/  key2; int /*<<< orphan*/  key1; } ;
typedef  int /*<<< orphan*/  keyInstance ;
typedef  int /*<<< orphan*/  cipherInstance ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* encrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* decrypt ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* reinit ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int AES_XTS_BLOCKSIZE ; 
#define  CRYPTO_AES_CBC 129 
#define  CRYPTO_AES_XTS 128 
 int /*<<< orphan*/  MODE_CBC ; 
 TYPE_1__ enc_xform_aes_xts ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int rijndael_blockDecrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int rijndael_blockEncrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int rijndael_cipherInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rijndael_makeKey (int /*<<< orphan*/ *,int,size_t,char const*) ; 
 int /*<<< orphan*/  rijndael_set_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
geliboot_crypt(u_int algo, int enc, u_char *data, size_t datasize,
    const u_char *key, size_t keysize, u_char *iv)
{
	keyInstance aeskey;
	cipherInstance cipher;
	struct aes_xts_ctx xtsctx, *ctxp;
	size_t xts_len;
	int err, blks, i;

	switch (algo) {
	case CRYPTO_AES_CBC:
		err = rijndael_makeKey(&aeskey, !enc, keysize, 
		    (const char *)key);
		if (err < 0) {
			printf("Failed to setup decryption keys: %d\n", err);
			return (err);
		}

		err = rijndael_cipherInit(&cipher, MODE_CBC, iv);
		if (err < 0) {
			printf("Failed to setup IV: %d\n", err);
			return (err);
		}

		if (enc == 0) {
			/* decrypt */
			blks = rijndael_blockDecrypt(&cipher, &aeskey, data, 
			    datasize * 8, data);
		} else {
			/* encrypt */
			blks = rijndael_blockEncrypt(&cipher, &aeskey, data, 
			    datasize * 8, data);
		}
		if (datasize != (blks / 8)) {
			printf("Failed to decrypt the entire input: "
			    "%u != %zu\n", blks, datasize);
			return (1);
		}
		break;
	case CRYPTO_AES_XTS:
		xts_len = keysize << 1;
		ctxp = &xtsctx;

		rijndael_set_key(&ctxp->key1, key, xts_len / 2);
		rijndael_set_key(&ctxp->key2, key + (xts_len / 16), xts_len / 2);

		enc_xform_aes_xts.reinit((caddr_t)ctxp, iv);

		switch (enc) {
		case 0: /* decrypt */
			for (i = 0; i < datasize; i += AES_XTS_BLOCKSIZE) {
				enc_xform_aes_xts.decrypt((caddr_t)ctxp, data + i);
			}
			break;
		case 1: /* encrypt */
			for (i = 0; i < datasize; i += AES_XTS_BLOCKSIZE) {
				enc_xform_aes_xts.encrypt((caddr_t)ctxp, data + i);
			}
			break;
		}
		break;
	default:
		printf("Unsupported crypto algorithm #%d\n", algo);
		return (1);
	}

	return (0);
}