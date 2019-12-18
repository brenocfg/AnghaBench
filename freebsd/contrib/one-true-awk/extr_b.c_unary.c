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
 int /*<<< orphan*/  NIL ; 
#define  PLUS 130 
#define  QUEST 129 
#define  STAR 128 
 int /*<<< orphan*/ * op2 (int const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int relex () ; 
 int rtok ; 

Node *unary(Node *np)
{
	switch (rtok) {
	case STAR:
		rtok = relex();
		return (unary(op2(STAR, np, NIL)));
	case PLUS:
		rtok = relex();
		return (unary(op2(PLUS, np, NIL)));
	case QUEST:
		rtok = relex();
		return (unary(op2(QUEST, np, NIL)));
	default:
		return (np);
	}
}