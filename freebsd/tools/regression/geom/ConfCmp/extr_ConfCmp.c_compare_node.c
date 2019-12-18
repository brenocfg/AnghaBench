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
struct node {char* name; char* id; char* ref; int /*<<< orphan*/  children; int /*<<< orphan*/  cont; } ;

/* Variables and functions */
 struct node* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct node* LIST_NEXT (struct node*,int /*<<< orphan*/ ) ; 
 int compare_node2 (struct node*,struct node*,int) ; 
 int /*<<< orphan*/  indent (int) ; 
 int /*<<< orphan*/  print_node (struct node*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int refcmp (char*,char*) ; 
 char* sbuf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siblings ; 
 int strcmp (char*,char*) ; 

__attribute__((used)) static int
compare_node(struct node *n1, struct node *n2, int in)
{
	int i;
	struct node *n1a, *n2a;

	i = strcmp(n1->name, n2->name);
	if (i)
		return (i);
	if (n1->id && n2->id)
		i = refcmp(n1->id, n2->id);
	else if (n1->id || n2->id)
		i = -1;
	if (i)
		return (i);
	if (n1->ref && n2->ref)
		i = refcmp(n1->ref, n2->ref);
	else if (n1->ref || n2->ref)
		i = -1;
	if (i)
		return (i);
	if (!strcmp(n1->name, "ref"))
		i = refcmp(sbuf_data(n1->cont), sbuf_data(n2->cont));
	else
		i = strcmp(sbuf_data(n1->cont), sbuf_data(n2->cont));
	if (i)
		return (1);
	n1a = LIST_FIRST(&n1->children);
	n2a = LIST_FIRST(&n2->children);
	for (;;) {
		if (n1a == NULL && n2a == NULL)
			return (0);
		if (n1a != NULL && n2a == NULL) {
			printf("1>");
			indent(in);
			print_node(n1a);
			printf("2>\n");
			return (1);
		}
		if (n1a == NULL && n2a != NULL) {
			printf("1>\n");
			printf("2>");
			indent(in);
			print_node(n2a);
			return (1);
		}
		i = compare_node2(n1a, n2a, in + 2);
		if (i)
			return (1);
		n1a = LIST_NEXT(n1a, siblings);
		n2a = LIST_NEXT(n2a, siblings);
	}
	return (0);
}