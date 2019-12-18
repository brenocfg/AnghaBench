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
typedef  union authctx {int dummy; } authctx ;
typedef  size_t u_int ;
struct TYPE_2__ {char* ipad; char* opad; struct auth_hash* auth_hash; } ;
struct ccp_session {TYPE_1__ hmac; } ;
struct auth_hash {int blocksize; int hashsize; int /*<<< orphan*/  (* Final ) (char*,union authctx*) ;int /*<<< orphan*/  (* Update ) (union authctx*,char*,int) ;int /*<<< orphan*/  (* Init ) (union authctx*) ;} ;
typedef  int /*<<< orphan*/  auth_ctx ;

/* Variables and functions */
 char HMAC_IPAD_VAL ; 
 char HMAC_OPAD_VAL ; 
 int /*<<< orphan*/  explicit_bzero (union authctx*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (union authctx*) ; 
 int /*<<< orphan*/  stub2 (union authctx*,char*,int) ; 
 int /*<<< orphan*/  stub3 (char*,union authctx*) ; 

__attribute__((used)) static void
ccp_init_hmac_digest(struct ccp_session *s, int cri_alg, char *key,
    int klen)
{
	union authctx auth_ctx;
	struct auth_hash *axf;
	u_int i;

	/*
	 * If the key is larger than the block size, use the digest of
	 * the key as the key instead.
	 */
	axf = s->hmac.auth_hash;
	klen /= 8;
	if (klen > axf->blocksize) {
		axf->Init(&auth_ctx);
		axf->Update(&auth_ctx, key, klen);
		axf->Final(s->hmac.ipad, &auth_ctx);
		explicit_bzero(&auth_ctx, sizeof(auth_ctx));
		klen = axf->hashsize;
	} else
		memcpy(s->hmac.ipad, key, klen);

	memset(s->hmac.ipad + klen, 0, axf->blocksize - klen);
	memcpy(s->hmac.opad, s->hmac.ipad, axf->blocksize);

	for (i = 0; i < axf->blocksize; i++) {
		s->hmac.ipad[i] ^= HMAC_IPAD_VAL;
		s->hmac.opad[i] ^= HMAC_OPAD_VAL;
	}
}