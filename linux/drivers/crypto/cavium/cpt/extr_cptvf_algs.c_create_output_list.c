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
typedef  int /*<<< orphan*/  u32 ;
struct cpt_request_info {int /*<<< orphan*/  outcnt; } ;
struct cvm_req_ctx {struct cpt_request_info cpt_req; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; int /*<<< orphan*/  dst; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 struct cvm_req_ctx* ablkcipher_request_ctx (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  update_output_data (struct cpt_request_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_output_iv (struct cpt_request_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void create_output_list(struct ablkcipher_request *req,
				      u32 enc_iv_len)
{
	struct cvm_req_ctx *rctx = ablkcipher_request_ctx(req);
	struct cpt_request_info *req_info = &rctx->cpt_req;
	u32 argcnt = 0;

	/* OUTPUT Buffer Processing
	 * AES encryption/decryption output would be
	 * received in the following format
	 *
	 * ------IV--------|------ENCRYPTED/DECRYPTED DATA-----|
	 * [ 16 Bytes/     [   Request Enc/Dec/ DATA Len AES CBC ]
	 */
	/* Reading IV information */
	update_output_iv(req_info, req->info, enc_iv_len, &argcnt);
	update_output_data(req_info, req->dst, req->nbytes, &argcnt);
	req_info->outcnt = argcnt;
}