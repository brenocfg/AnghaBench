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
typedef  int /*<<< orphan*/  u8 ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 scalar_t__ SHA224_DIGEST_SIZE ; 
 scalar_t__ crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int sha224_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sha256_final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int crypto_sha256_final(struct shash_desc *desc, u8 *out)
{
	if (crypto_shash_digestsize(desc->tfm) == SHA224_DIGEST_SIZE)
		return sha224_final(shash_desc_ctx(desc), out);
	else
		return sha256_final(shash_desc_ctx(desc), out);
}