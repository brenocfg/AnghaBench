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
struct slabhash {int /*<<< orphan*/ * array; } ;
struct lruhash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 struct lruhash_entry* lruhash_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 size_t slab_idx (struct slabhash*,int /*<<< orphan*/ ) ; 

struct lruhash_entry* slabhash_lookup(struct slabhash* sl, 
	hashvalue_type hash, void* key, int wr)
{
	return lruhash_lookup(sl->array[slab_idx(sl, hash)], hash, key, wr);
}