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
struct scatterlist {int offset; scalar_t__ length; } ;
struct crypto_hash_walk {int offset; scalar_t__ entrylen; scalar_t__ total; struct scatterlist* sg; scalar_t__ pg; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int hash_walk_next (struct crypto_hash_walk*) ; 
 int offset_in_page (int) ; 
 scalar_t__ sg_page (struct scatterlist*) ; 

__attribute__((used)) static int hash_walk_new_entry(struct crypto_hash_walk *walk)
{
	struct scatterlist *sg;

	sg = walk->sg;
	walk->offset = sg->offset;
	walk->pg = sg_page(walk->sg) + (walk->offset >> PAGE_SHIFT);
	walk->offset = offset_in_page(walk->offset);
	walk->entrylen = sg->length;

	if (walk->entrylen > walk->total)
		walk->entrylen = walk->total;
	walk->total -= walk->entrylen;

	return hash_walk_next(walk);
}