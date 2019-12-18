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
struct string_list {struct string_list* next; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int COMMA ; 
 int SEMI ; 
 int STRING ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,size_t) ; 
 struct string_list* new_string_list (size_t) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 

void
parse_string_list(FILE *cfile, struct string_list **lp, int multiple)
{
	int			 token;
	char			*val;
	size_t			 valsize;
	struct string_list	*cur, *tmp;

	/* Find the last medium in the media list. */
	if (*lp)
		for (cur = *lp; cur->next; cur = cur->next)
			;	/* nothing */
	else
		cur = NULL;

	do {
		token = next_token(&val, cfile);
		if (token != STRING) {
			parse_warn("Expecting media options.");
			skip_to_semi(cfile);
			return;
		}

		valsize = strlen(val) + 1;
		tmp = new_string_list(valsize);
		if (tmp == NULL)
			error("no memory for string list entry.");
		memcpy(tmp->string, val, valsize);
		tmp->next = NULL;

		/* Store this medium at the end of the media list. */
		if (cur)
			cur->next = tmp;
		else
			*lp = tmp;
		cur = tmp;

		token = next_token(&val, cfile);
	} while (multiple && token == COMMA);

	if (token != SEMI) {
		parse_warn("expecting semicolon.");
		skip_to_semi(cfile);
	}
}