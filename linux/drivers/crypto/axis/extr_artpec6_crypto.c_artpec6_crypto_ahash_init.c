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
 int artpec6_crypto_ahash_init_common (struct crypto_tfm*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int artpec6_crypto_ahash_init(struct crypto_tfm *tfm)
{
	return artpec6_crypto_ahash_init_common(tfm, NULL);
}