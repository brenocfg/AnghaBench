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
struct delta_base_cache_key {int dummy; } ;
struct delta_base_cache_entry {struct delta_base_cache_key const key; } ;

/* Variables and functions */
 int /*<<< orphan*/  delta_base_cache_key_eq (struct delta_base_cache_key const*,struct delta_base_cache_key const*) ; 

__attribute__((used)) static int delta_base_cache_hash_cmp(const void *unused_cmp_data,
				     const void *va, const void *vb,
				     const void *vkey)
{
	const struct delta_base_cache_entry *a = va, *b = vb;
	const struct delta_base_cache_key *key = vkey;
	if (key)
		return !delta_base_cache_key_eq(&a->key, key);
	else
		return !delta_base_cache_key_eq(&a->key, &b->key);
}