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
typedef  int /*<<< orphan*/ * Tree ;
struct TYPE_2__ {scalar_t__ ref; } ;
typedef  int /*<<< orphan*/  Swtch ;
typedef  int /*<<< orphan*/  Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
#define  ID 129 
#define  IF 128 
 int /*<<< orphan*/  branch (int) ; 
 int /*<<< orphan*/  conditional ; 
 int /*<<< orphan*/  definelab (int) ; 
 int /*<<< orphan*/  definept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  expr0 ; 
 TYPE_1__* findlabel (int) ; 
 int foldcond (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t gettok () ; 
 scalar_t__* kind ; 
 double refinc ; 
 int /*<<< orphan*/  src ; 
 int /*<<< orphan*/  statement (int,int /*<<< orphan*/ ,int) ; 
 size_t t ; 
 int /*<<< orphan*/  test (char,char*) ; 
 int /*<<< orphan*/ * texpr (int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void forstmt(int lab, Swtch swp, int lev) {
	int once = 0;
	Tree e1 = NULL, e2 = NULL, e3 = NULL;
	Coordinate pt2, pt3;
	
	t = gettok();
	expect('(');
	definept(NULL);
	if (kind[t] == ID)
		e1 = texpr(expr0, ';', FUNC);
	else
		expect(';');
	walk(e1, 0, 0);
	pt2 = src;
	refinc *= 10.0;
	if (kind[t] == ID)
		e2 = texpr(conditional, ';', FUNC);
	else
		expect(';');
	pt3 = src;
	if (kind[t] == ID)
		e3 = texpr(expr0, ')', FUNC);
	else {
		static char stop[] = { IF, ID, '}', 0 };
		test(')', stop);
	}
	if (e2) {
		once = foldcond(e1, e2);
		if (!once)
			branch(lab + 3);
	}
	definelab(lab);
	statement(lab, swp, lev);
	definelab(lab + 1);
	definept(&pt3);
	if (e3)
		walk(e3, 0, 0);
	if (e2) {
		if (!once)
			definelab(lab + 3);
		definept(&pt2);
		walk(e2, lab, 0);
	} else {
		definept(&pt2);
		branch(lab);
	}
	if (findlabel(lab + 2)->ref)
		definelab(lab + 2);
}