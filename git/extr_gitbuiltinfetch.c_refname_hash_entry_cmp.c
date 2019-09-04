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
struct refname_hash_entry {void const* refname; } ;

/* Variables and functions */
 int strcmp (void const*,void const*) ; 

__attribute__((used)) static int refname_hash_entry_cmp(const void *hashmap_cmp_fn_data,
				  const void *e1_,
				  const void *e2_,
				  const void *keydata)
{
	const struct refname_hash_entry *e1 = e1_;
	const struct refname_hash_entry *e2 = e2_;

	return strcmp(e1->refname, keydata ? keydata : e2->refname);
}