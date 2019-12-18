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
struct alg {int type; } ;

/* Variables and functions */
#define  T_AUTHENC 133 
#define  T_BLKCIPHER 132 
#define  T_CCM 131 
#define  T_GCM 130 
#define  T_HASH 129 
#define  T_HMAC 128 
 int /*<<< orphan*/  run_authenc_test (struct alg*,size_t) ; 
 int /*<<< orphan*/  run_blkcipher_test (struct alg*,size_t) ; 
 int /*<<< orphan*/  run_ccm_test (struct alg*,size_t) ; 
 int /*<<< orphan*/  run_gcm_test (struct alg*,size_t) ; 
 int /*<<< orphan*/  run_hash_test (struct alg*,size_t) ; 
 int /*<<< orphan*/  run_hmac_test (struct alg*,size_t) ; 

__attribute__((used)) static void
run_test(struct alg *alg, size_t size)
{

	switch (alg->type) {
	case T_HASH:
		run_hash_test(alg, size);
		break;
	case T_HMAC:
		run_hmac_test(alg, size);
		break;
	case T_BLKCIPHER:
		run_blkcipher_test(alg, size);
		break;
	case T_AUTHENC:
		run_authenc_test(alg, size);
		break;
	case T_GCM:
		run_gcm_test(alg, size);
		break;
	case T_CCM:
		run_ccm_test(alg, size);
		break;
	}
}