#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  nonce; } ;
struct TYPE_6__ {int /*<<< orphan*/  hmac_ctx; TYPE_1__ challenge; } ;
typedef  TYPE_2__ ntlm_client ;

/* Variables and functions */
 int /*<<< orphan*/  NTLM_NTLM2_HASH_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ntlm_client_set_errmsg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ntlm_hmac_ctx_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntlm_hmac_md5_final (unsigned char*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntlm_hmac_md5_init (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntlm_hmac_md5_update (int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

__attribute__((used)) static bool generate_ntlm2_challengehash(
	unsigned char out[16],
	ntlm_client *ntlm,
	unsigned char ntlm2_hash[NTLM_NTLM2_HASH_LEN],
	const unsigned char *blob,
	size_t blob_len)
{
	size_t out_len = 16;

	if (!ntlm_hmac_ctx_reset(ntlm->hmac_ctx) ||
		!ntlm_hmac_md5_init(ntlm->hmac_ctx,
			ntlm2_hash, NTLM_NTLM2_HASH_LEN) ||
		!ntlm_hmac_md5_update(ntlm->hmac_ctx,
			(const unsigned char *)&ntlm->challenge.nonce, 8) ||
		!ntlm_hmac_md5_update(ntlm->hmac_ctx, blob, blob_len) ||
		!ntlm_hmac_md5_final(out, &out_len, ntlm->hmac_ctx)) {
		ntlm_client_set_errmsg(ntlm, "failed to create HMAC-MD5");
		return false;
	}

	assert(out_len == 16);
	return true;
}