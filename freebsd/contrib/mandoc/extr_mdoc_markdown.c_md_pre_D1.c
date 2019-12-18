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
 scalar_t__ code_blocks ; 
 int /*<<< orphan*/  md_stack (char) ; 
 int /*<<< orphan*/  outflags ; 
 int /*<<< orphan*/  quote_blocks ; 

__attribute__((used)) static int
md_pre_D1(struct roff_node *n)
{
	/*
	 * Markdown blockquote syntax does not work inside code blocks.
	 * The best we can do is fall back to another nested code block.
	 */
	if (code_blocks) {
		md_stack('\t');
		code_blocks++;
	} else {
		md_stack('>');
		quote_blocks++;
	}
	outflags |= MD_sp;
	return 1;
}