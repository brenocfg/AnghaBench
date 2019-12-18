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
 int /*<<< orphan*/  MD_sp ; 
 int NODE_SYNPRETTY ; 
 int /*<<< orphan*/  md_word (char*) ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static void
md_post_Fn(struct roff_node *n)
{
	md_word(")");
	if (n->flags & NODE_SYNPRETTY) {
		md_word(";");
		outflags |= MD_sp;
	}
}