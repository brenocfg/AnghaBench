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
typedef  int u8 ;
typedef  int u32 ;
struct crypto_ahash {int dummy; } ;
struct cc_hash_ctx {int inter_digestsize; int hash_len; } ;
struct ahash_request {int dummy; } ;
struct ahash_req_ctx {int* digest_buff; int* digest_bytes_len; } ;

/* Variables and functions */
 int CC_EXPORT_MAGIC ; 
 struct ahash_req_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int* cc_hash_buf (struct ahash_req_ctx*) ; 
 int* cc_hash_buf_cnt (struct ahash_req_ctx*) ; 
 struct cc_hash_ctx* crypto_ahash_ctx (struct crypto_ahash*) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 

__attribute__((used)) static int cc_hash_export(struct ahash_request *req, void *out)
{
	struct crypto_ahash *ahash = crypto_ahash_reqtfm(req);
	struct cc_hash_ctx *ctx = crypto_ahash_ctx(ahash);
	struct ahash_req_ctx *state = ahash_request_ctx(req);
	u8 *curr_buff = cc_hash_buf(state);
	u32 curr_buff_cnt = *cc_hash_buf_cnt(state);
	const u32 tmp = CC_EXPORT_MAGIC;

	memcpy(out, &tmp, sizeof(u32));
	out += sizeof(u32);

	memcpy(out, state->digest_buff, ctx->inter_digestsize);
	out += ctx->inter_digestsize;

	memcpy(out, state->digest_bytes_len, ctx->hash_len);
	out += ctx->hash_len;

	memcpy(out, &curr_buff_cnt, sizeof(u32));
	out += sizeof(u32);

	memcpy(out, curr_buff, curr_buff_cnt);

	return 0;
}