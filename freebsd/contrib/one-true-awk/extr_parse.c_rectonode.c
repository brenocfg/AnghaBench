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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Cell ;

/* Variables and functions */
 int /*<<< orphan*/  CUNK ; 
 int /*<<< orphan*/  INDIRECT ; 
 int /*<<< orphan*/  celltonode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * op1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Node *rectonode(void)	/* make $0 into a Node */
{
	extern Cell *literal0;
	return op1(INDIRECT, celltonode(literal0, CUNK));
}