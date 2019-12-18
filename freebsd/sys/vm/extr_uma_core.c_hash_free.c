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
struct uma_hash {scalar_t__ uh_hashsize; int /*<<< orphan*/ * uh_slab_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_UMAHASH ; 
 int /*<<< orphan*/  SKIP_NONE ; 
 scalar_t__ UMA_HASH_SIZE_INIT ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashzone ; 
 int /*<<< orphan*/  zone_free_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hash_free(struct uma_hash *hash)
{
	if (hash->uh_slab_hash == NULL)
		return;
	if (hash->uh_hashsize == UMA_HASH_SIZE_INIT)
		zone_free_item(hashzone, hash->uh_slab_hash, NULL, SKIP_NONE);
	else
		free(hash->uh_slab_hash, M_UMAHASH);
}