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
struct pack_idx_entry {int dummy; } ;
struct object_entry {int /*<<< orphan*/  hash; } ;
struct hashfile {int dummy; } ;
typedef  int /*<<< orphan*/  hash_value ;

/* Variables and functions */
 int /*<<< orphan*/  hashwrite (struct hashfile*,size_t*,int) ; 
 size_t htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_hash_cache(struct hashfile *f,
			     struct pack_idx_entry **index,
			     uint32_t index_nr)
{
	uint32_t i;

	for (i = 0; i < index_nr; ++i) {
		struct object_entry *entry = (struct object_entry *)index[i];
		uint32_t hash_value = htonl(entry->hash);
		hashwrite(f, &hash_value, sizeof(hash_value));
	}
}