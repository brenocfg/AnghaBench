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
struct test_entry {scalar_t__ key; int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  st_add4 (int,size_t,size_t,int) ; 
 size_t strlen (char*) ; 
 struct test_entry* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct test_entry *alloc_test_entry(unsigned int hash,
					   char *key, char *value)
{
	size_t klen = strlen(key);
	size_t vlen = strlen(value);
	struct test_entry *entry = xmalloc(st_add4(sizeof(*entry), klen, vlen, 2));
	hashmap_entry_init(&entry->ent, hash);
	memcpy(entry->key, key, klen + 1);
	memcpy(entry->key + klen + 1, value, vlen + 1);
	return entry;
}