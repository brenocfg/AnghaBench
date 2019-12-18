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
struct ignoretab {int /*<<< orphan*/  i_count; struct ignore** i_head; } ;
struct ignore {struct ignore* i_link; void* i_field; } ;
typedef  int /*<<< orphan*/  field ;

/* Variables and functions */
 int LINESIZE ; 
 void* calloc (unsigned int,int) ; 
 int hash (char*) ; 
 int igshow (struct ignoretab*,char const*) ; 
 int /*<<< orphan*/  istrncpy (char*,char*,int) ; 
 scalar_t__ member (char*,struct ignoretab*) ; 
 int /*<<< orphan*/  strcpy (void*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
ignore1(char **list, struct ignoretab *tab, const char *which)
{
	char field[LINESIZE];
	char **ap;
	struct ignore *igp;
	int h;

	if (*list == NULL)
		return (igshow(tab, which));
	for (ap = list; *ap != 0; ap++) {
		istrncpy(field, *ap, sizeof(field));
		if (member(field, tab))
			continue;
		h = hash(field);
		igp = calloc(1, sizeof(struct ignore));
		igp->i_field = calloc((unsigned)strlen(field) + 1,
		    sizeof(char));
		strcpy(igp->i_field, field);
		igp->i_link = tab->i_head[h];
		tab->i_head[h] = igp;
		tab->i_count++;
	}
	return (0);
}