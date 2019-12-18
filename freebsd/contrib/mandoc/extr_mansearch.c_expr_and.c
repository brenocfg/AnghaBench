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
struct mansearch {int dummy; } ;
struct expr {struct expr* next; struct expr* child; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_AND ; 
 void* exprterm (struct mansearch const*,int,char**,int*) ; 
 struct expr* mandoc_calloc (int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static struct expr *
expr_and(const struct mansearch *search, int argc, char *argv[], int *argi)
{
	struct expr	*parent, *child;
	int		 needterm;

	needterm = 1;
	parent = child = NULL;
	while (*argi < argc) {
		if (strcmp(")", argv[*argi]) == 0) {
			if (needterm)
				warnx("missing term "
				    "before closing parenthesis");
			needterm = 0;
			break;
		}
		if (strcmp("-o", argv[*argi]) == 0)
			break;
		if (strcmp("-a", argv[*argi]) == 0) {
			if (needterm) {
				if (*argi > 0)
					warnx("ignoring -a after %s",
					    argv[*argi - 1]);
				else
					warnx("ignoring initial -a");
			}
			needterm = 1;
			++*argi;
			continue;
		}
		if (needterm == 0)
			break;
		if (child == NULL) {
			child = exprterm(search, argc, argv, argi);
			if (child != NULL)
				needterm = 0;
			continue;
		}
		needterm = 0;
		if (parent == NULL) {
			parent = mandoc_calloc(1, sizeof(*parent));
			parent->type = EXPR_AND;
			parent->next = NULL;
			parent->child = child;
		}
		child->next = exprterm(search, argc, argv, argi);
		if (child->next != NULL) {
			child = child->next;
			needterm = 0;
		}
	}
	if (needterm && *argi)
		warnx("ignoring trailing %s", argv[*argi - 1]);
	return parent == NULL ? child : parent;
}