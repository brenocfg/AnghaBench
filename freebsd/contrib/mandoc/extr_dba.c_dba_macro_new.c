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
struct dba {int /*<<< orphan*/  pages; int /*<<< orphan*/  macros; } ;
typedef  int int32_t ;

/* Variables and functions */
 int be32toh (int const) ; 
 int /*<<< orphan*/  dba_array_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dba_array_get (int /*<<< orphan*/ ,int) ; 
 struct macro_entry* get_macro_entry (int /*<<< orphan*/ ,char const*,int) ; 

void
dba_macro_new(struct dba *dba, int32_t im, const char *value,
    const int32_t *pp)
{
	struct macro_entry	*entry;
	const int32_t		*ip;
	int32_t			 np;

	np = 0;
	for (ip = pp; *ip; ip++)
		np++;

	entry = get_macro_entry(dba_array_get(dba->macros, im), value, np);
	for (ip = pp; *ip; ip++)
		dba_array_add(entry->pages, dba_array_get(dba->pages,
		    be32toh(*ip) / 5 / sizeof(*ip) - 1));
}