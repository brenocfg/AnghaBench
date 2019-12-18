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
struct ohash {int dummy; } ;
struct macro_entry {int /*<<< orphan*/  pages; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBA_GROW ; 
 int /*<<< orphan*/  dba_array_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct macro_entry* mandoc_malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 struct macro_entry* ohash_find (struct ohash*,unsigned int) ; 
 int /*<<< orphan*/  ohash_insert (struct ohash*,unsigned int,struct macro_entry*) ; 
 unsigned int ohash_qlookup (struct ohash*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct macro_entry *
get_macro_entry(struct ohash *macro, const char *value, int32_t np)
{
	struct macro_entry	*entry;
	size_t			 len;
	unsigned int		 slot;

	slot = ohash_qlookup(macro, value);
	if ((entry = ohash_find(macro, slot)) == NULL) {
		len = strlen(value) + 1;
		entry = mandoc_malloc(sizeof(*entry) + len);
		memcpy(&entry->value, value, len);
		entry->pages = dba_array_new(np, DBA_GROW);
		ohash_insert(macro, slot, entry);
	}
	return entry;
}