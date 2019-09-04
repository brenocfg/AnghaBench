#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int* hash; } ;
struct pack_midx_entry {TYPE_1__ oid; } ;
struct hashfile {int dummy; } ;

/* Variables and functions */
 size_t MIDX_CHUNK_FANOUT_SIZE ; 
 int /*<<< orphan*/  hashwrite_be32 (struct hashfile*,int) ; 

__attribute__((used)) static size_t write_midx_oid_fanout(struct hashfile *f,
				    struct pack_midx_entry *objects,
				    uint32_t nr_objects)
{
	struct pack_midx_entry *list = objects;
	struct pack_midx_entry *last = objects + nr_objects;
	uint32_t count = 0;
	uint32_t i;

	/*
	* Write the first-level table (the list is sorted,
	* but we use a 256-entry lookup to be able to avoid
	* having to do eight extra binary search iterations).
	*/
	for (i = 0; i < 256; i++) {
		struct pack_midx_entry *next = list;

		while (next < last && next->oid.hash[0] == i) {
			count++;
			next++;
		}

		hashwrite_be32(f, count);
		list = next;
	}

	return MIDX_CHUNK_FANOUT_SIZE;
}