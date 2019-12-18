#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  Swtch ;

/* Variables and functions */
 scalar_t__ ELSE ; 
 int /*<<< orphan*/  branch (int) ; 
 int /*<<< orphan*/  conditional (char) ; 
 int /*<<< orphan*/  definelab (int) ; 
 int /*<<< orphan*/  definept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* findlabel (int) ; 
 scalar_t__ gettok () ; 
 double refinc ; 
 int /*<<< orphan*/  statement (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ t ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ifstmt(int lab, int loop, Swtch swp, int lev) {
	t = gettok();
	expect('(');
	definept(NULL);
	walk(conditional(')'), 0, lab);
	refinc /= 2.0;
	statement(loop, swp, lev);
	if (t == ELSE) {
		branch(lab + 1);
		t = gettok();
		definelab(lab);
		statement(loop, swp, lev);
		if (findlabel(lab + 1)->ref)
			definelab(lab + 1);
	} else
		definelab(lab);
}