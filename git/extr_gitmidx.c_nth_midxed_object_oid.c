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
typedef  int uint32_t ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct multi_pack_index {int num_objects; int hash_len; scalar_t__ chunk_oid_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,scalar_t__) ; 

struct object_id *nth_midxed_object_oid(struct object_id *oid,
					struct multi_pack_index *m,
					uint32_t n)
{
	if (n >= m->num_objects)
		return NULL;

	hashcpy(oid->hash, m->chunk_oid_lookup + m->hash_len * n);
	return oid;
}