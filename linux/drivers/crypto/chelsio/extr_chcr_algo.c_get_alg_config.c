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
struct algo_param {int result_size; int /*<<< orphan*/  auth_mode; void* mk_size; } ;

/* Variables and functions */
 void* CHCR_KEYCTX_MAC_KEY_SIZE_160 ; 
 void* CHCR_KEYCTX_MAC_KEY_SIZE_256 ; 
 void* CHCR_KEYCTX_MAC_KEY_SIZE_512 ; 
 int /*<<< orphan*/  CHCR_SCMD_AUTH_MODE_SHA1 ; 
 int /*<<< orphan*/  CHCR_SCMD_AUTH_MODE_SHA224 ; 
 int /*<<< orphan*/  CHCR_SCMD_AUTH_MODE_SHA256 ; 
 int /*<<< orphan*/  CHCR_SCMD_AUTH_MODE_SHA512_384 ; 
 int /*<<< orphan*/  CHCR_SCMD_AUTH_MODE_SHA512_512 ; 
 int EINVAL ; 
#define  SHA1_DIGEST_SIZE 132 
#define  SHA224_DIGEST_SIZE 131 
#define  SHA256_DIGEST_SIZE 130 
#define  SHA384_DIGEST_SIZE 129 
#define  SHA512_DIGEST_SIZE 128 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int get_alg_config(struct algo_param *params,
			  unsigned int auth_size)
{
	switch (auth_size) {
	case SHA1_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_160;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA1;
		params->result_size = SHA1_DIGEST_SIZE;
		break;
	case SHA224_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA224;
		params->result_size = SHA256_DIGEST_SIZE;
		break;
	case SHA256_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_256;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA256;
		params->result_size = SHA256_DIGEST_SIZE;
		break;
	case SHA384_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_512;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA512_384;
		params->result_size = SHA512_DIGEST_SIZE;
		break;
	case SHA512_DIGEST_SIZE:
		params->mk_size = CHCR_KEYCTX_MAC_KEY_SIZE_512;
		params->auth_mode = CHCR_SCMD_AUTH_MODE_SHA512_512;
		params->result_size = SHA512_DIGEST_SIZE;
		break;
	default:
		pr_err("chcr : ERROR, unsupported digest size\n");
		return -EINVAL;
	}
	return 0;
}