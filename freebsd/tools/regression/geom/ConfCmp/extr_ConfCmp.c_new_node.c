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
struct node {int /*<<< orphan*/  children; void* key; void* cont; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 struct node* calloc (int,int) ; 
 int /*<<< orphan*/  sbuf_clear (void*) ; 
 void* sbuf_new_auto () ; 

__attribute__((used)) static struct node *
new_node(void)
{
	struct node *np;

	np = calloc(1, sizeof *np);
	np->cont = sbuf_new_auto();
	sbuf_clear(np->cont);
	np->key = sbuf_new_auto();
	sbuf_clear(np->key);
	LIST_INIT(&np->children);
	return (np);
}