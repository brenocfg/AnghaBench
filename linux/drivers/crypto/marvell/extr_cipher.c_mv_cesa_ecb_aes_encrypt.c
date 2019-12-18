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
struct skcipher_request {int dummy; } ;
struct mv_cesa_op_ctx {int dummy; } ;

/* Variables and functions */
 int CESA_SA_DESC_CFG_CRYPTCM_ECB ; 
 int CESA_SA_DESC_CFG_DIR_ENC ; 
 int mv_cesa_aes_op (struct skcipher_request*,struct mv_cesa_op_ctx*) ; 
 int /*<<< orphan*/  mv_cesa_set_op_cfg (struct mv_cesa_op_ctx*,int) ; 

__attribute__((used)) static int mv_cesa_ecb_aes_encrypt(struct skcipher_request *req)
{
	struct mv_cesa_op_ctx tmpl;

	mv_cesa_set_op_cfg(&tmpl,
			   CESA_SA_DESC_CFG_CRYPTCM_ECB |
			   CESA_SA_DESC_CFG_DIR_ENC);

	return mv_cesa_aes_op(req, &tmpl);
}