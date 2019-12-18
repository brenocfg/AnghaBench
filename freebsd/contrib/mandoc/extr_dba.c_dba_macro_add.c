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
struct macro_entry {int /*<<< orphan*/  pages; } ;
struct dba_array {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  dba_array_add (int /*<<< orphan*/ ,struct dba_array*) ; 
 int /*<<< orphan*/  dba_array_get (struct dba_array*,int /*<<< orphan*/ ) ; 
 struct macro_entry* get_macro_entry (int /*<<< orphan*/ ,char const*,int) ; 

void
dba_macro_add(struct dba_array *macros, int32_t im, const char *value,
    struct dba_array *page)
{
	struct macro_entry	*entry;

	if (*value == '\0')
		return;
	entry = get_macro_entry(dba_array_get(macros, im), value, 1);
	dba_array_add(entry->pages, page);
}