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
struct node {char* name; char* id; char* ref; int /*<<< orphan*/  key; int /*<<< orphan*/  cont; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 char* sbuf_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_node(struct node *np)
{
	printf("\"%s\" -- \"%s\" -- \"%s\"", np->name, sbuf_data(np->cont), sbuf_data(np->key));
	if (np->id)
		printf(" id=\"%s\"", np->id);
	if (np->ref)
		printf(" ref=\"%s\"", np->ref);
	printf("\n");
}