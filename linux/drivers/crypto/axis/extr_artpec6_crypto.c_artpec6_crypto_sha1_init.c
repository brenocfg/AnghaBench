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
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARTPEC6_CRYPTO_HASH_SHA1 ; 
 int artpec6_crypto_init_hash (struct ahash_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int artpec6_crypto_sha1_init(struct ahash_request *req)
{
	return artpec6_crypto_init_hash(req, ARTPEC6_CRYPTO_HASH_SHA1, 0);
}