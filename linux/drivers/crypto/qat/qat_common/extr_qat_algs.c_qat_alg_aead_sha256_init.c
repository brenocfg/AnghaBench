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
struct crypto_aead {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_QAT_HW_AUTH_ALGO_SHA256 ; 
 int qat_alg_aead_init (struct crypto_aead*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qat_alg_aead_sha256_init(struct crypto_aead *tfm)
{
	return qat_alg_aead_init(tfm, ICP_QAT_HW_AUTH_ALGO_SHA256, "sha256");
}