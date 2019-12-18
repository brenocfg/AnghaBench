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
struct crypto {int /*<<< orphan*/  verify_tfm; int /*<<< orphan*/  csums_tfm; int /*<<< orphan*/  integrity_tfm; int /*<<< orphan*/  cram_hmac_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_crypto(struct crypto *crypto)
{
	crypto_free_shash(crypto->cram_hmac_tfm);
	crypto_free_shash(crypto->integrity_tfm);
	crypto_free_shash(crypto->csums_tfm);
	crypto_free_shash(crypto->verify_tfm);
}