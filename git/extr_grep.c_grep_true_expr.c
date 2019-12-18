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
struct grep_expr {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GREP_NODE_TRUE ; 
 struct grep_expr* xcalloc (int,int) ; 

__attribute__((used)) static struct grep_expr *grep_true_expr(void)
{
	struct grep_expr *z = xcalloc(1, sizeof(*z));
	z->node = GREP_NODE_TRUE;
	return z;
}