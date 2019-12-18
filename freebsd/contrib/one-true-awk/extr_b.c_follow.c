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

/* Variables and functions */
#define  CAT 132 
 int FINAL ; 
#define  OR 131 
#define  PLUS 130 
#define  QUEST 129 
#define  STAR 128 
 int /*<<< orphan*/  first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * right (int /*<<< orphan*/ *) ; 
 int type (int /*<<< orphan*/ *) ; 

void follow(Node *v)	/* collects leaves that can follow v into setvec */
{
	Node *p;

	if (type(v) == FINAL)
		return;
	p = parent(v);
	switch (type(p)) {
	case STAR:
	case PLUS:
		first(v);
		follow(p);
		return;

	case OR:
	case QUEST:
		follow(p);
		return;

	case CAT:
		if (v == left(p)) {	/* v is left child of p */
			if (first(right(p)) == 0) {
				follow(p);
				return;
			}
		} else		/* v is right child */
			follow(p);
		return;
	}
}