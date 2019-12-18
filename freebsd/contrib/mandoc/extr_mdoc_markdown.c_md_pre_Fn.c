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
struct roff_node {struct roff_node* next; struct roff_node* child; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 int /*<<< orphan*/  md_node (struct roff_node*) ; 
 int /*<<< orphan*/  md_pre_Fa (struct roff_node*) ; 
 int /*<<< orphan*/  md_pre_syn (struct roff_node*) ; 
 int /*<<< orphan*/  md_rawword (char*) ; 
 int /*<<< orphan*/  md_word (char*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static int
md_pre_Fn(struct roff_node *n)
{
	md_pre_syn(n);

	if ((n = n->child) == NULL)
		return 0;

	md_rawword("**");
	outflags &= ~MD_spc;
	md_node(n);
	outflags &= ~MD_spc;
	md_rawword("**");
	outflags &= ~MD_spc;
	md_word("(");

	if ((n = n->next) != NULL)
		md_pre_Fa(n);
	return 0;
}