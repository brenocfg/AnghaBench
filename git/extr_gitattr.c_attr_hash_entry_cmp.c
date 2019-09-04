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
struct attr_hash_entry {scalar_t__ keylen; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int attr_hash_entry_cmp(const void *unused_cmp_data,
			       const void *entry,
			       const void *entry_or_key,
			       const void *unused_keydata)
{
	const struct attr_hash_entry *a = entry;
	const struct attr_hash_entry *b = entry_or_key;
	return (a->keylen != b->keylen) || strncmp(a->key, b->key, a->keylen);
}