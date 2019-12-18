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
typedef  int /*<<< orphan*/  uint32_t ;
struct namedobjects_head {int dummy; } ;
struct namedobj_instance {int nn_size; int nv_size; int /*<<< orphan*/  max_blocks; int /*<<< orphan*/  idx_mask; int /*<<< orphan*/  cmp_f; int /*<<< orphan*/  hash_f; struct namedobjects_head* values; struct namedobjects_head* names; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int NAMEDOBJ_HASH_SIZE ; 
 int /*<<< orphan*/  TAILQ_INIT (struct namedobjects_head*) ; 
 int /*<<< orphan*/  ipfw_objhash_bitmap_alloc (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 struct namedobj_instance* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  objhash_cmp_name ; 
 int /*<<< orphan*/  objhash_hash_name ; 

struct namedobj_instance *
ipfw_objhash_create(uint32_t items)
{
	struct namedobj_instance *ni;
	int i;
	size_t size;

	size = sizeof(struct namedobj_instance) +
	    sizeof(struct namedobjects_head) * NAMEDOBJ_HASH_SIZE +
	    sizeof(struct namedobjects_head) * NAMEDOBJ_HASH_SIZE;

	ni = malloc(size, M_IPFW, M_WAITOK | M_ZERO);
	ni->nn_size = NAMEDOBJ_HASH_SIZE;
	ni->nv_size = NAMEDOBJ_HASH_SIZE;

	ni->names = (struct namedobjects_head *)(ni +1);
	ni->values = &ni->names[ni->nn_size];

	for (i = 0; i < ni->nn_size; i++)
		TAILQ_INIT(&ni->names[i]);

	for (i = 0; i < ni->nv_size; i++)
		TAILQ_INIT(&ni->values[i]);

	/* Set default hashing/comparison functions */
	ni->hash_f = objhash_hash_name;
	ni->cmp_f = objhash_cmp_name;

	/* Allocate bitmask separately due to possible resize */
	ipfw_objhash_bitmap_alloc(items, (void*)&ni->idx_mask, &ni->max_blocks);

	return (ni);
}