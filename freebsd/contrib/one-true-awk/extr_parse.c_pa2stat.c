#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  ntype; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  NSTAT ; 
 scalar_t__ PA2NUM ; 
 int /*<<< orphan*/  PASTAT2 ; 
 int /*<<< orphan*/  SYNTAX (char*,scalar_t__) ; 
 int /*<<< orphan*/  itonp (int /*<<< orphan*/ ) ; 
 TYPE_1__* node4 (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paircnt ; 

Node *pa2stat(Node *a, Node *b, Node *c)	/* pat, pat {...} */
{
	Node *x;

	x = node4(PASTAT2, a, b, c, itonp(paircnt));
	if (paircnt++ >= PA2NUM)
		SYNTAX( "limited to %d pat,pat statements", PA2NUM );
	x->ntype = NSTAT;
	return(x);
}