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

/* Variables and functions */
 scalar_t__ CHAR ; 
 size_t EOI ; 
 int /*<<< orphan*/  FUNC ; 
 int /*<<< orphan*/  GLOBAL ; 
 size_t ID ; 
 scalar_t__ STATIC ; 
 int /*<<< orphan*/  STMT ; 
 int /*<<< orphan*/  dclglobal ; 
 int /*<<< orphan*/  deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 size_t gettok () ; 
 int glevel ; 
 scalar_t__* kind ; 
 int /*<<< orphan*/  level ; 
 size_t t ; 
 int /*<<< orphan*/  warning (char*) ; 
 scalar_t__ xref ; 

void program(void) {
	int n;
	
	level = GLOBAL;
	for (n = 0; t != EOI; n++)
		if (kind[t] == CHAR || kind[t] == STATIC
		|| t == ID || t == '*' || t == '(') {
			decl(dclglobal);
			deallocate(STMT);
			if (!(glevel >= 3 || xref))
			deallocate(FUNC);
		} else if (t == ';') {
			warning("empty declaration\n");
			t = gettok();
		} else {
			error("unrecognized declaration\n");
			t = gettok();
		}
	if (n == 0)
		warning("empty input file\n");
}