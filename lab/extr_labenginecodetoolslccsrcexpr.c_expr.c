#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Tree ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
#define  ID 129 
#define  IF 128 
 int /*<<< orphan*/  RIGHT ; 
 TYPE_1__* expr1 (int /*<<< orphan*/ ) ; 
 char gettok () ; 
 TYPE_1__* pointer (TYPE_1__*) ; 
 int /*<<< orphan*/  root (int /*<<< orphan*/ ) ; 
 char t ; 
 int /*<<< orphan*/  test (int,char*) ; 
 TYPE_1__* tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  value (TYPE_1__*) ; 

Tree expr(int tok) {
	static char stop[] = { IF, ID, '}', 0 };
	Tree p = expr1(0);

	while (t == ',') {
		Tree q;
		t = gettok();
		q = pointer(expr1(0));
		p = tree(RIGHT, q->type, root(value(p)), q);
	}
	if (tok)	
		test(tok, stop);
	return p;
}