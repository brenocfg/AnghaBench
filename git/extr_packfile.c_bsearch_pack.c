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
typedef  int /*<<< orphan*/  uint32_t ;
struct packed_git {unsigned char* index_data; int index_version; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int bsearch_hash (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* the_hash_algo ; 

int bsearch_pack(const struct object_id *oid, const struct packed_git *p, uint32_t *result)
{
	const unsigned char *index_fanout = p->index_data;
	const unsigned char *index_lookup;
	const unsigned int hashsz = the_hash_algo->rawsz;
	int index_lookup_width;

	if (!index_fanout)
		BUG("bsearch_pack called without a valid pack-index");

	index_lookup = index_fanout + 4 * 256;
	if (p->index_version == 1) {
		index_lookup_width = hashsz + 4;
		index_lookup += 4;
	} else {
		index_lookup_width = hashsz;
		index_fanout += 8;
		index_lookup += 8;
	}

	return bsearch_hash(oid->hash, (const uint32_t*)index_fanout,
			    index_lookup, index_lookup_width, result);
}