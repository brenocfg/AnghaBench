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
typedef  void dba_array ;
typedef  enum form { ____Placeholder_form } form ;

/* Variables and functions */
 int DBA_GROW ; 
 int DBA_STR ; 
 int DBP_MAX ; 
 int /*<<< orphan*/  dba_array_add (void*,void*) ; 
 void* dba_array_new (int,int) ; 
 void* mandoc_strdup (char const*) ; 
 void* prepend (char const*,int) ; 

struct dba_array *
dba_page_new(struct dba_array *pages, const char *arch,
    const char *desc, const char *file, enum form form)
{
	struct dba_array *page, *entry;

	page = dba_array_new(DBP_MAX, 0);
	entry = dba_array_new(1, DBA_STR | DBA_GROW);
	dba_array_add(page, entry);
	entry = dba_array_new(1, DBA_STR | DBA_GROW);
	dba_array_add(page, entry);
	if (arch != NULL && *arch != '\0') {
		entry = dba_array_new(1, DBA_STR | DBA_GROW);
		dba_array_add(entry, (void *)arch);
	} else
		entry = NULL;
	dba_array_add(page, entry);
	dba_array_add(page, mandoc_strdup(desc));
	entry = dba_array_new(1, DBA_STR | DBA_GROW);
	dba_array_add(entry, prepend(file, form));
	dba_array_add(page, entry);
	dba_array_add(pages, page);
	return page;
}