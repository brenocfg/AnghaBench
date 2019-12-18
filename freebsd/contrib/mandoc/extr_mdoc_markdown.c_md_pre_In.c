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
struct roff_node {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_spc ; 
 int NODE_SYNPRETTY ; 
 int /*<<< orphan*/  md_pre_syn (struct roff_node*) ; 
 int /*<<< orphan*/  md_rawword (char*) ; 
 int /*<<< orphan*/  md_word (char*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static int
md_pre_In(struct roff_node *n)
{
	if (n->flags & NODE_SYNPRETTY) {
		md_pre_syn(n);
		md_rawword("**");
		outflags &= ~MD_spc;
		md_word("#include <");
	} else {
		md_word("<");
		outflags &= ~MD_spc;
		md_rawword("*");
	}
	outflags &= ~MD_spc;
	return 1;
}