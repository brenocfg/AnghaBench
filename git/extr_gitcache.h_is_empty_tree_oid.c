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
struct TYPE_2__ {int /*<<< orphan*/  empty_tree; } ;

/* Variables and functions */
 int oideq (struct object_id const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static inline int is_empty_tree_oid(const struct object_id *oid)
{
	return oideq(oid, the_hash_algo->empty_tree);
}