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
struct namedobj_instance {int /*<<< orphan*/ * cmp_f; int /*<<< orphan*/ * hash_f; } ;
typedef  int /*<<< orphan*/  objhash_hash_f ;
typedef  int /*<<< orphan*/  objhash_cmp_f ;

/* Variables and functions */

void
ipfw_objhash_set_funcs(struct namedobj_instance *ni, objhash_hash_f *hash_f,
    objhash_cmp_f *cmp_f)
{

	ni->hash_f = hash_f;
	ni->cmp_f = cmp_f;
}