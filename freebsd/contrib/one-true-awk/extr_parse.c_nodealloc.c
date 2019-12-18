#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lineno; int /*<<< orphan*/ * nnext; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*) ; 
 int /*<<< orphan*/  lineno ; 
 scalar_t__ malloc (int) ; 

Node *nodealloc(int n)
{
	Node *x;

	x = (Node *) malloc(sizeof(Node) + (n-1)*sizeof(Node *));
	if (x == NULL)
		FATAL("out of space in nodealloc");
	x->nnext = NULL;
	x->lineno = lineno;
	return(x);
}