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
typedef  int /*<<< orphan*/  uiEntry ;

/* Variables and functions */
 int /*<<< orphan*/ * finishNewEntry (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_search_entry_new () ; 

uiEntry *uiNewSearchEntry(void)
{
	return finishNewEntry(gtk_search_entry_new(), "search-changed");
}