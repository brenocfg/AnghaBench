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
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NOHOME ; 
 int /*<<< orphan*/  ERR_UNKUSER ; 
 int /*<<< orphan*/  STRnonomatch ; 
 char* Strnsave (char*,int) ; 
 char* Strsave (char*) ; 
 char* Strspl (char*,char*) ; 
 scalar_t__ adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* gethdir (char*) ; 
 int /*<<< orphan*/  short2str (char*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static Char *
globtilde(Char *s)
{
    Char *name, *u, *home, *res;

    u = s;
    for (s++; *s && *s != '/' && *s != ':'; s++)
	continue;
    name = Strnsave(u + 1, s - (u + 1));
    cleanup_push(name, xfree);
    home = gethdir(name);
    if (home == NULL) {
	if (adrof(STRnonomatch)) {
	    cleanup_until(name);
	    return u;
	}
	if (*name)
	    stderror(ERR_UNKUSER, short2str(name));
	else
	    stderror(ERR_NOHOME);
    }
    cleanup_until(name);
    if (home[0] == '/' && home[1] == '\0' && s[0] == '/')
	res = Strsave(s);
    else
	res = Strspl(home, s);
    xfree(home);
    xfree(u);
    return res;
}