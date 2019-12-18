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
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_HASH160_LEN ; 
 int /*<<< orphan*/  SA_HASH_ALG_SHA1 ; 
 int /*<<< orphan*/  SA_HASH_MODE_HASH ; 
 int crypto4xx_hash_alg_init (struct crypto_tfm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int crypto4xx_sha1_alg_init(struct crypto_tfm *tfm)
{
	return crypto4xx_hash_alg_init(tfm, SA_HASH160_LEN, SA_HASH_ALG_SHA1,
				       SA_HASH_MODE_HASH);
}