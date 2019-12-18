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
struct shash_desc {int dummy; } ;
struct crypto_hash_walk {int /*<<< orphan*/  data; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int crypto_hash_walk_done (struct crypto_hash_walk*,int) ; 
 int crypto_hash_walk_first (struct ahash_request*,struct crypto_hash_walk*) ; 
 int crypto_shash_update (struct shash_desc*,int /*<<< orphan*/ ,int) ; 

int shash_ahash_update(struct ahash_request *req, struct shash_desc *desc)
{
	struct crypto_hash_walk walk;
	int nbytes;

	for (nbytes = crypto_hash_walk_first(req, &walk); nbytes > 0;
	     nbytes = crypto_hash_walk_done(&walk, nbytes))
		nbytes = crypto_shash_update(desc, walk.data, nbytes);

	return nbytes;
}