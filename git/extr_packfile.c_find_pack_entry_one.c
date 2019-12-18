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
struct packed_git {unsigned char* index_data; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ bsearch_pack (struct object_id*,struct packed_git*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  nth_packed_object_offset (struct packed_git*,int /*<<< orphan*/ ) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 

off_t find_pack_entry_one(const unsigned char *sha1,
				  struct packed_git *p)
{
	const unsigned char *index = p->index_data;
	struct object_id oid;
	uint32_t result;

	if (!index) {
		if (open_pack_index(p))
			return 0;
	}

	hashcpy(oid.hash, sha1);
	if (bsearch_pack(&oid, p, &result))
		return nth_packed_object_offset(p, result);
	return 0;
}