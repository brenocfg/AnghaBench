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
struct roff_node {scalar_t__ type; char* string; struct roff_node* next; } ;
struct html {int indent; } ;

/* Variables and functions */
 scalar_t__ ROFFT_COMMENT ; 
 int /*<<< orphan*/  print_endline (struct html*) ; 
 int /*<<< orphan*/  print_indent (struct html*) ; 
 int /*<<< orphan*/  print_word (struct html*,char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

void
print_gen_comment(struct html *h, struct roff_node *n)
{
	int	 wantblank;

	print_word(h, "<!-- This is an automatically generated file."
	    "  Do not edit.");
	h->indent = 1;
	wantblank = 0;
	while (n != NULL && n->type == ROFFT_COMMENT) {
		if (strstr(n->string, "-->") == NULL &&
		    (wantblank || *n->string != '\0')) {
			print_endline(h);
			print_indent(h);
			print_word(h, n->string);
			wantblank = *n->string != '\0';
		}
		n = n->next;
	}
	if (wantblank)
		print_endline(h);
	print_word(h, " -->");
	print_endline(h);
	h->indent = 0;
}