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
struct object_id {int dummy; } ;
struct hashmap {int dummy; } ;
struct TYPE_2__ {size_t rawsz; } ;

/* Variables and functions */
 struct object_id const* anonymize_mem (struct hashmap*,int /*<<< orphan*/ ,struct object_id const*,size_t*) ; 
 int /*<<< orphan*/  generate_fake_oid ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static const struct object_id *anonymize_oid(const struct object_id *oid)
{
	static struct hashmap objs;
	size_t len = the_hash_algo->rawsz;
	return anonymize_mem(&objs, generate_fake_oid, oid, &len);
}