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
struct roff_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_sp ; 
 int /*<<< orphan*/  code_blocks ; 
 int /*<<< orphan*/  md_stack (char) ; 
 int /*<<< orphan*/  outflags ; 
 scalar_t__ quote_blocks ; 

__attribute__((used)) static int
md_pre_Dl(struct roff_node *n)
{
	/*
	 * Markdown code block syntax does not work inside blockquotes.
	 * The best we can do is fall back to another nested blockquote.
	 */
	if (quote_blocks) {
		md_stack('>');
		quote_blocks++;
	} else {
		md_stack('\t');
		code_blocks++;
	}
	outflags |= MD_sp;
	return 1;
}