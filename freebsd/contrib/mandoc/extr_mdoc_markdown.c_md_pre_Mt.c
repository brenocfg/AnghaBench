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
struct roff_node {struct roff_node* next; int /*<<< orphan*/  string; struct roff_node* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 int /*<<< orphan*/  md_rawword (char*) ; 
 int /*<<< orphan*/  md_uri (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outcount ; 
 int /*<<< orphan*/  outflags ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static int
md_pre_Mt(struct roff_node *n)
{
	const struct roff_node *nch;

	md_rawword("[");
	outflags &= ~MD_spc;
	for (nch = n->child; nch != NULL; nch = nch->next)
		md_word(nch->string);
	outflags &= ~MD_spc;
	md_rawword("](mailto:");
	for (nch = n->child; nch != NULL; nch = nch->next) {
		md_uri(nch->string);
		if (nch->next != NULL) {
			putchar(' ');
			outcount++;
		}
	}
	outflags &= ~MD_spc;
	md_rawword(")");
	return 0;
}