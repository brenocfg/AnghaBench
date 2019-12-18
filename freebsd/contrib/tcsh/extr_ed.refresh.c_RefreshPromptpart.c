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
typedef  int Char ;

/* Variables and functions */
 int CHAR ; 
 int /*<<< orphan*/  Draw (int*,int,int) ; 
 int LITERAL ; 
 int /*<<< orphan*/  MakeLiteral (int*,int,int /*<<< orphan*/ ) ; 
 int NLSWidth (int) ; 
 int /*<<< orphan*/  Vdraw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
RefreshPromptpart(Char *buf)
{
    Char *cp;
    int w;

    if (buf == NULL)
	return;
    for (cp = buf; *cp; ) {
	if (*cp & LITERAL) {
	    Char *litstart = cp;
	    while (*cp & LITERAL)
		cp++;
	    if (*cp) {
		w = NLSWidth(*cp & CHAR);
		Vdraw(MakeLiteral(litstart, cp + 1 - litstart, 0), w);
		cp++;
	    }
	    else {
		/*
		 * XXX: This is a bug, we lose the last literal, if it is not
		 * followed by a normal character, but it is too hard to fix
		 */
		break;
	    }
	}
	else
	    cp += Draw(cp, cp == buf, 1);
    }
}