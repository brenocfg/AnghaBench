#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mv_cesa_dev {TYPE_1__* caps; } ;
struct TYPE_2__ {int nahash_algs; int ncipher_algs; int /*<<< orphan*/ * cipher_algs; int /*<<< orphan*/ * ahash_algs; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_skcipher (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv_cesa_remove_algs(struct mv_cesa_dev *cesa)
{
	int i;

	for (i = 0; i < cesa->caps->nahash_algs; i++)
		crypto_unregister_ahash(cesa->caps->ahash_algs[i]);

	for (i = 0; i < cesa->caps->ncipher_algs; i++)
		crypto_unregister_skcipher(cesa->caps->cipher_algs[i]);
}