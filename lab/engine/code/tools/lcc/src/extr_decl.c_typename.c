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
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 int Aflag ; 
 int /*<<< orphan*/  dclr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hasproto (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  specifier (int /*<<< orphan*/ *) ; 
 char t ; 
 int /*<<< orphan*/  warning (char*) ; 

Type typename(void) {
	Type ty = specifier(NULL);

	if (t == '*' || t == '(' || t == '[') {
		ty = dclr(ty, NULL, NULL, 1);
		if (Aflag >= 1 && !hasproto(ty))
			warning("missing prototype\n");
	}
	return ty;
}