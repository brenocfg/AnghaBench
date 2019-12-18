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
 char* Cursor ; 
 char HIST ; 
 char* InputBuf ; 
 int /*<<< orphan*/  Refresh () ; 
 int c_excl (char*) ; 

__attribute__((used)) static int
c_substitute(void)
{
    Char *p;
    int  nr_exp;

    /*
     * Start p out one character before the cursor.  Move it backwards looking
     * for white space, the beginning of the line, or a history character.
     */
    for (p = Cursor - 1; 
	 p > InputBuf && *p != ' ' && *p != '\t' && *p && *p != HIST; --p)
	continue;

    /*
     * If we found a history character, go expand it.
     */
    if (p >= InputBuf && HIST != '\0' && *p == HIST)
	nr_exp = c_excl(p);
    else
        nr_exp = 0;
    Refresh();

    return nr_exp;
}