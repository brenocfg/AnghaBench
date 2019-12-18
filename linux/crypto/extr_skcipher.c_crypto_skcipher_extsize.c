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
struct crypto_blkcipher {int dummy; } ;
struct crypto_alg {int /*<<< orphan*/ * cra_type; } ;
struct crypto_ablkcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ablkcipher_type ; 
 unsigned int crypto_alg_extsize (struct crypto_alg*) ; 
 int /*<<< orphan*/  crypto_blkcipher_type ; 

__attribute__((used)) static unsigned int crypto_skcipher_extsize(struct crypto_alg *alg)
{
	if (alg->cra_type == &crypto_blkcipher_type)
		return sizeof(struct crypto_blkcipher *);

	if (alg->cra_type == &crypto_ablkcipher_type)
		return sizeof(struct crypto_ablkcipher *);

	return crypto_alg_extsize(alg);
}