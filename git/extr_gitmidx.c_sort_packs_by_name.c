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
typedef  size_t uint32_t ;
struct pack_pair {size_t pack_int_id; char* pack_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct pack_pair*,size_t) ; 
 int /*<<< orphan*/  QSORT (struct pack_pair*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct pack_pair*) ; 
 int /*<<< orphan*/  pack_pair_compare ; 

__attribute__((used)) static void sort_packs_by_name(char **pack_names, uint32_t nr_packs, uint32_t *perm)
{
	uint32_t i;
	struct pack_pair *pairs;

	ALLOC_ARRAY(pairs, nr_packs);

	for (i = 0; i < nr_packs; i++) {
		pairs[i].pack_int_id = i;
		pairs[i].pack_name = pack_names[i];
	}

	QSORT(pairs, nr_packs, pack_pair_compare);

	for (i = 0; i < nr_packs; i++) {
		pack_names[i] = pairs[i].pack_name;
		perm[pairs[i].pack_int_id] = i;
	}

	free(pairs);
}