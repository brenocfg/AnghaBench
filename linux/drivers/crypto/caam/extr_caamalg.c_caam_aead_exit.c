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
 int /*<<< orphan*/  caam_exit_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_ctx (struct crypto_aead*) ; 

__attribute__((used)) static void caam_aead_exit(struct crypto_aead *tfm)
{
	caam_exit_common(crypto_aead_ctx(tfm));
}