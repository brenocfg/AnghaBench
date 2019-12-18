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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/ * Itoa (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * STR1 ; 
 int /*<<< orphan*/  STRKSHLVL ; 
 int /*<<< orphan*/  STRshlvl ; 
 int /*<<< orphan*/  Unsetenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  cleanup_ignore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (int /*<<< orphan*/ *) ; 
 char* getenv (char*) ; 
 scalar_t__ loginsh ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsetenv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsetv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

void
shlvl(int val)
{
    char *cp;

    if ((cp = getenv("SHLVL")) != NULL) {

	if (loginsh)
	    val = 1;
	else
	    val += atoi(cp);

	if (val <= 0) {
	    if (adrof(STRshlvl) != NULL)
		unsetv(STRshlvl);
	    Unsetenv(STRKSHLVL);
	}
	else {
	    Char *p;

	    p = Itoa(val, 0, 0);
	    cleanup_push(p, xfree);
	    setv(STRshlvl, p, VAR_READWRITE);
	    cleanup_ignore(p);
	    cleanup_until(p);
	    tsetenv(STRKSHLVL, p);
	}
    }
    else {
	setcopy(STRshlvl, STR1, VAR_READWRITE);
	tsetenv(STRKSHLVL, STR1);
    }
}