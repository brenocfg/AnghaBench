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
struct cipher_tfm {int /*<<< orphan*/  cit_decrypt_one; int /*<<< orphan*/  cit_encrypt_one; int /*<<< orphan*/  cit_setkey; } ;
struct crypto_tfm {TYPE_1__* __crt_alg; struct cipher_tfm crt_cipher; } ;
struct cipher_alg {int /*<<< orphan*/  cia_decrypt; int /*<<< orphan*/  cia_encrypt; } ;
struct TYPE_2__ {struct cipher_alg cra_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  cipher_decrypt_unaligned ; 
 int /*<<< orphan*/  cipher_encrypt_unaligned ; 
 scalar_t__ crypto_tfm_alg_alignmask (struct crypto_tfm*) ; 
 int /*<<< orphan*/  setkey ; 

int crypto_init_cipher_ops(struct crypto_tfm *tfm)
{
	struct cipher_tfm *ops = &tfm->crt_cipher;
	struct cipher_alg *cipher = &tfm->__crt_alg->cra_cipher;

	ops->cit_setkey = setkey;
	ops->cit_encrypt_one = crypto_tfm_alg_alignmask(tfm) ?
		cipher_encrypt_unaligned : cipher->cia_encrypt;
	ops->cit_decrypt_one = crypto_tfm_alg_alignmask(tfm) ?
		cipher_decrypt_unaligned : cipher->cia_decrypt;

	return 0;
}