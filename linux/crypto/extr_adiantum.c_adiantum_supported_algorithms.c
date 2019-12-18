#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cra_name; } ;
struct skcipher_alg {TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  cra_name; } ;
struct shash_alg {TYPE_1__ base; } ;
struct TYPE_6__ {scalar_t__ cia_min_keysize; scalar_t__ cia_max_keysize; } ;
struct crypto_alg {scalar_t__ cra_blocksize; TYPE_3__ cra_cipher; } ;

/* Variables and functions */
 scalar_t__ BLOCKCIPHER_BLOCK_SIZE ; 
 scalar_t__ BLOCKCIPHER_KEY_SIZE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool adiantum_supported_algorithms(struct skcipher_alg *streamcipher_alg,
					  struct crypto_alg *blockcipher_alg,
					  struct shash_alg *hash_alg)
{
	if (strcmp(streamcipher_alg->base.cra_name, "xchacha12") != 0 &&
	    strcmp(streamcipher_alg->base.cra_name, "xchacha20") != 0)
		return false;

	if (blockcipher_alg->cra_cipher.cia_min_keysize > BLOCKCIPHER_KEY_SIZE ||
	    blockcipher_alg->cra_cipher.cia_max_keysize < BLOCKCIPHER_KEY_SIZE)
		return false;
	if (blockcipher_alg->cra_blocksize != BLOCKCIPHER_BLOCK_SIZE)
		return false;

	if (strcmp(hash_alg->base.cra_name, "nhpoly1305") != 0)
		return false;

	return true;
}