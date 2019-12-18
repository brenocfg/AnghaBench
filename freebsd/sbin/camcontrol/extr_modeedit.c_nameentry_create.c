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
struct pagename {int page; int subpage; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  RTRIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pagename*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link ; 
 struct pagename* malloc (int) ; 
 int /*<<< orphan*/  namelist ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static void
nameentry_create(int page, int subpage, char *name) {
	struct pagename *newentry;

	if (page < 0 || subpage < 0 || name == NULL || name[0] == '\0')
		return;

	/* Allocate memory for the new entry and a copy of the entry name. */
	if ((newentry = malloc(sizeof(struct pagename))) == NULL ||
	    (newentry->name = strdup(name)) == NULL)
		err(EX_OSERR, NULL);

	/* Trim any trailing whitespace for the page name. */
	RTRIM(newentry->name);

	newentry->page = page;
	newentry->subpage = subpage;
	SLIST_INSERT_HEAD(&namelist, newentry, link);
}