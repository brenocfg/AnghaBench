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
struct object_id {int /*<<< orphan*/  hash; } ;
struct multi_pack_index {int /*<<< orphan*/  chunk_oid_lookup; int /*<<< orphan*/  chunk_oid_fanout; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIDX_HASH_LEN ; 
 int bsearch_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bsearch_midx(const struct object_id *oid, struct multi_pack_index *m, uint32_t *result)
{
	return bsearch_hash(oid->hash, m->chunk_oid_fanout, m->chunk_oid_lookup,
			    MIDX_HASH_LEN, result);
}