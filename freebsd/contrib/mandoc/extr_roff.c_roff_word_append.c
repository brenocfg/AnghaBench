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
struct roff_node {char* string; } ;
struct roff_man {int /*<<< orphan*/  next; int /*<<< orphan*/  roff; struct roff_node* last; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROFF_NEXT_SIBLING ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mandoc_asprintf (char**,char*,char*,char*) ; 
 char* roff_strdup (int /*<<< orphan*/ ,char const*) ; 

void
roff_word_append(struct roff_man *man, const char *word)
{
	struct roff_node	*n;
	char			*addstr, *newstr;

	n = man->last;
	addstr = roff_strdup(man->roff, word);
	mandoc_asprintf(&newstr, "%s %s", n->string, addstr);
	free(addstr);
	free(n->string);
	n->string = newstr;
	man->next = ROFF_NEXT_SIBLING;
}