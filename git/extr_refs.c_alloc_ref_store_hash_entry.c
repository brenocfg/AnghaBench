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
struct ref_store_hash_entry {struct ref_store* refs; int /*<<< orphan*/  ent; } ;
struct ref_store {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_STR (struct ref_store_hash_entry*,char const*,char const*) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strhash (char const*) ; 

__attribute__((used)) static struct ref_store_hash_entry *alloc_ref_store_hash_entry(
		const char *name, struct ref_store *refs)
{
	struct ref_store_hash_entry *entry;

	FLEX_ALLOC_STR(entry, name, name);
	hashmap_entry_init(&entry->ent, strhash(name));
	entry->refs = refs;
	return entry;
}