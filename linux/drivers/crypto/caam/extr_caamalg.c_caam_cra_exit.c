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
struct crypto_skcipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  caam_exit_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_ctx (struct crypto_skcipher*) ; 

__attribute__((used)) static void caam_cra_exit(struct crypto_skcipher *tfm)
{
	caam_exit_common(crypto_skcipher_ctx(tfm));
}