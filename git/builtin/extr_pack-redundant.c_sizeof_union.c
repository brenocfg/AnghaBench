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
struct packed_git {unsigned char* index_data; int index_version; unsigned long num_objects; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 int hashcmp (unsigned char const*,unsigned char const*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static size_t sizeof_union(struct packed_git *p1, struct packed_git *p2)
{
	size_t ret = 0;
	unsigned long p1_off = 0, p2_off = 0, p1_step, p2_step;
	const unsigned char *p1_base, *p2_base;
	const unsigned int hashsz = the_hash_algo->rawsz;

	p1_base = p1->index_data;
	p2_base = p2->index_data;
	p1_base += 256 * 4 + ((p1->index_version < 2) ? 4 : 8);
	p2_base += 256 * 4 + ((p2->index_version < 2) ? 4 : 8);
	p1_step = hashsz + ((p1->index_version < 2) ? 4 : 0);
	p2_step = hashsz + ((p2->index_version < 2) ? 4 : 0);

	while (p1_off < p1->num_objects * p1_step &&
	       p2_off < p2->num_objects * p2_step)
	{
		int cmp = hashcmp(p1_base + p1_off, p2_base + p2_off);
		/* cmp ~ p1 - p2 */
		if (cmp == 0) {
			ret++;
			p1_off += p1_step;
			p2_off += p2_step;
			continue;
		}
		if (cmp < 0) { /* p1 has the object, p2 doesn't */
			p1_off += p1_step;
		} else { /* p2 has the object, p1 doesn't */
			p2_off += p2_step;
		}
	}
	return ret;
}