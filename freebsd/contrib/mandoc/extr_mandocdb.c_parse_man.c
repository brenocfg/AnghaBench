#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct roff_node {scalar_t__ type; scalar_t__ tok; struct roff_node* next; struct roff_node* child; int /*<<< orphan*/  string; TYPE_1__* parent; } ;
struct roff_meta {int /*<<< orphan*/  title; } ;
struct mpage {int name_head_done; int /*<<< orphan*/ * desc; } ;
struct TYPE_2__ {struct roff_node* head; } ;

/* Variables and functions */
 scalar_t__ MAN_SH ; 
 int /*<<< orphan*/  NAME_HEAD ; 
 int /*<<< orphan*/  NAME_TITLE ; 
 scalar_t__ ROFFT_BODY ; 
 scalar_t__ ROFFT_TEXT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  deroff (char**,struct roff_node const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/ * mandoc_strndup (char*,int) ; 
 int /*<<< orphan*/  putkey (struct mpage*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static void
parse_man(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{
	const struct roff_node *head, *body;
	char		*start, *title;
	char		 byte;
	size_t		 sz;

	if (n == NULL)
		return;

	/*
	 * We're only searching for one thing: the first text child in
	 * the BODY of a NAME section.  Since we don't keep track of
	 * sections in -man, run some hoops to find out whether we're in
	 * the correct section or not.
	 */

	if (n->type == ROFFT_BODY && n->tok == MAN_SH) {
		body = n;
		if ((head = body->parent->head) != NULL &&
		    (head = head->child) != NULL &&
		    head->next == NULL &&
		    head->type == ROFFT_TEXT &&
		    strcmp(head->string, "NAME") == 0 &&
		    body->child != NULL) {

			/*
			 * Suck the entire NAME section into memory.
			 * Yes, we might run away.
			 * But too many manuals have big, spread-out
			 * NAME sections over many lines.
			 */

			title = NULL;
			deroff(&title, body);
			if (NULL == title)
				return;

			/*
			 * Go through a special heuristic dance here.
			 * Conventionally, one or more manual names are
			 * comma-specified prior to a whitespace, then a
			 * dash, then a description.  Try to puzzle out
			 * the name parts here.
			 */

			start = title;
			for ( ;; ) {
				sz = strcspn(start, " ,");
				if ('\0' == start[sz])
					break;

				byte = start[sz];
				start[sz] = '\0';

				/*
				 * Assume a stray trailing comma in the
				 * name list if a name begins with a dash.
				 */

				if ('-' == start[0] ||
				    ('\\' == start[0] && '-' == start[1]))
					break;

				putkey(mpage, start, NAME_TITLE);
				if ( ! (mpage->name_head_done ||
				    strcasecmp(start, meta->title))) {
					putkey(mpage, start, NAME_HEAD);
					mpage->name_head_done = 1;
				}

				if (' ' == byte) {
					start += sz + 1;
					break;
				}

				assert(',' == byte);
				start += sz + 1;
				while (' ' == *start)
					start++;
			}

			if (start == title) {
				putkey(mpage, start, NAME_TITLE);
				if ( ! (mpage->name_head_done ||
				    strcasecmp(start, meta->title))) {
					putkey(mpage, start, NAME_HEAD);
					mpage->name_head_done = 1;
				}
				free(title);
				return;
			}

			while (isspace((unsigned char)*start))
				start++;

			if (0 == strncmp(start, "-", 1))
				start += 1;
			else if (0 == strncmp(start, "\\-\\-", 4))
				start += 4;
			else if (0 == strncmp(start, "\\-", 2))
				start += 2;
			else if (0 == strncmp(start, "\\(en", 4))
				start += 4;
			else if (0 == strncmp(start, "\\(em", 4))
				start += 4;

			while (' ' == *start)
				start++;

			/*
			 * Cut off excessive one-line descriptions.
			 * Bad pages are not worth better heuristics.
			 */

			mpage->desc = mandoc_strndup(start, 150);
			free(title);
			return;
		}
	}

	for (n = n->child; n; n = n->next) {
		if (NULL != mpage->desc)
			break;
		parse_man(mpage, meta, n);
	}
}