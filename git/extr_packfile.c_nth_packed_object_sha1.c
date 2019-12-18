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
typedef  unsigned int const uint32_t ;
struct packed_git {unsigned char* index_data; unsigned int const num_objects; int index_version; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 scalar_t__ open_pack_index (struct packed_git*) ; 
 TYPE_1__* the_hash_algo ; 

const unsigned char *nth_packed_object_sha1(struct packed_git *p,
					    uint32_t n)
{
	const unsigned char *index = p->index_data;
	const unsigned int hashsz = the_hash_algo->rawsz;
	if (!index) {
		if (open_pack_index(p))
			return NULL;
		index = p->index_data;
	}
	if (n >= p->num_objects)
		return NULL;
	index += 4 * 256;
	if (p->index_version == 1) {
		return index + (hashsz + 4) * n + 4;
	} else {
		index += 8;
		return index + hashsz * n;
	}
}