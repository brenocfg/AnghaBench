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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_tfm {TYPE_1__* __crt_alg; } ;
struct cipher_alg {int /*<<< orphan*/  (* cia_encrypt ) (struct crypto_tfm*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ;} ;
struct TYPE_2__ {struct cipher_alg cra_cipher; } ;

/* Variables and functions */
 int /*<<< orphan*/  cipher_crypt_unaligned (int /*<<< orphan*/  (*) (struct crypto_tfm*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*),struct crypto_tfm*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 unsigned long crypto_tfm_alg_alignmask (struct crypto_tfm*) ; 
 int /*<<< orphan*/  stub1 (struct crypto_tfm*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static void cipher_encrypt_unaligned(struct crypto_tfm *tfm,
				     u8 *dst, const u8 *src)
{
	unsigned long alignmask = crypto_tfm_alg_alignmask(tfm);
	struct cipher_alg *cipher = &tfm->__crt_alg->cra_cipher;

	if (unlikely(((unsigned long)dst | (unsigned long)src) & alignmask)) {
		cipher_crypt_unaligned(cipher->cia_encrypt, tfm, dst, src);
		return;
	}

	cipher->cia_encrypt(tfm, dst, src);
}