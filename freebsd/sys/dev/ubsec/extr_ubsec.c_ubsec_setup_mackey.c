#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ubsec_session {int /*<<< orphan*/  ses_hmouter; int /*<<< orphan*/  ses_hminner; } ;
typedef  int* caddr_t ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int /*<<< orphan*/  b32; } ;
struct TYPE_9__ {TYPE_1__ h; } ;
typedef  TYPE_2__ SHA1_CTX ;
typedef  TYPE_3__ MD5_CTX ;

/* Variables and functions */
 int CRYPTO_MD5_HMAC ; 
 int HMAC_IPAD_VAL ; 
 int HMAC_OPAD_VAL ; 
 int /*<<< orphan*/  MD5Init (TYPE_3__*) ; 
 int /*<<< orphan*/  MD5Update (TYPE_3__*,int*,int) ; 
 int MD5_BLOCK_LEN ; 
 int /*<<< orphan*/  SHA1Init (TYPE_2__*) ; 
 int /*<<< orphan*/  SHA1Update (TYPE_2__*,int*,int) ; 
 int SHA1_BLOCK_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* hmac_ipad_buffer ; 
 int* hmac_opad_buffer ; 

__attribute__((used)) static void
ubsec_setup_mackey(struct ubsec_session *ses, int algo, caddr_t key, int klen)
{
	MD5_CTX md5ctx;
	SHA1_CTX sha1ctx;
	int i;

	for (i = 0; i < klen; i++)
		key[i] ^= HMAC_IPAD_VAL;

	if (algo == CRYPTO_MD5_HMAC) {
		MD5Init(&md5ctx);
		MD5Update(&md5ctx, key, klen);
		MD5Update(&md5ctx, hmac_ipad_buffer, MD5_BLOCK_LEN - klen);
		bcopy(md5ctx.state, ses->ses_hminner, sizeof(md5ctx.state));
	} else {
		SHA1Init(&sha1ctx);
		SHA1Update(&sha1ctx, key, klen);
		SHA1Update(&sha1ctx, hmac_ipad_buffer,
		    SHA1_BLOCK_LEN - klen);
		bcopy(sha1ctx.h.b32, ses->ses_hminner, sizeof(sha1ctx.h.b32));
	}

	for (i = 0; i < klen; i++)
		key[i] ^= (HMAC_IPAD_VAL ^ HMAC_OPAD_VAL);

	if (algo == CRYPTO_MD5_HMAC) {
		MD5Init(&md5ctx);
		MD5Update(&md5ctx, key, klen);
		MD5Update(&md5ctx, hmac_opad_buffer, MD5_BLOCK_LEN - klen);
		bcopy(md5ctx.state, ses->ses_hmouter, sizeof(md5ctx.state));
	} else {
		SHA1Init(&sha1ctx);
		SHA1Update(&sha1ctx, key, klen);
		SHA1Update(&sha1ctx, hmac_opad_buffer,
		    SHA1_BLOCK_LEN - klen);
		bcopy(sha1ctx.h.b32, ses->ses_hmouter, sizeof(sha1ctx.h.b32));
	}

	for (i = 0; i < klen; i++)
		key[i] ^= HMAC_OPAD_VAL;
}