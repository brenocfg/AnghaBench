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
struct TYPE_2__ {scalar_t__ has_cfb64; scalar_t__ has_gcm; scalar_t__ has_xts; scalar_t__ has_authenc; } ;
struct atmel_aes_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * aes_algs ; 
 int /*<<< orphan*/ * aes_authenc_algs ; 
 int /*<<< orphan*/  aes_cfb64_alg ; 
 int /*<<< orphan*/  aes_gcm_alg ; 
 int /*<<< orphan*/  aes_xts_alg ; 
 int /*<<< orphan*/  crypto_unregister_aead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atmel_aes_unregister_algs(struct atmel_aes_dev *dd)
{
	int i;

#ifdef CONFIG_CRYPTO_DEV_ATMEL_AUTHENC
	if (dd->caps.has_authenc)
		for (i = 0; i < ARRAY_SIZE(aes_authenc_algs); i++)
			crypto_unregister_aead(&aes_authenc_algs[i]);
#endif

	if (dd->caps.has_xts)
		crypto_unregister_alg(&aes_xts_alg);

	if (dd->caps.has_gcm)
		crypto_unregister_aead(&aes_gcm_alg);

	if (dd->caps.has_cfb64)
		crypto_unregister_alg(&aes_cfb64_alg);

	for (i = 0; i < ARRAY_SIZE(aes_algs); i++)
		crypto_unregister_alg(&aes_algs[i]);
}