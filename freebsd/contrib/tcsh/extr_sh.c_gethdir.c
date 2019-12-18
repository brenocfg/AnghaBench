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
 char* STRNULL ; 
 int /*<<< orphan*/  STRhome ; 
 char* Strsave (char*) ; 
 char* gettilde (char const*) ; 
 char* varval (int /*<<< orphan*/ ) ; 

Char *
gethdir(const Char *home)
{
    Char   *h;

    /*
     * Is it us?
     */
    if (*home == '\0') {
	if ((h = varval(STRhome)) != STRNULL)
	    return Strsave(h);
	else
	    return NULL;
    }

    /*
     * Look in the cache
     */
    if ((h = gettilde(home)) == NULL)
	return NULL;
    else
	return Strsave(h);
}