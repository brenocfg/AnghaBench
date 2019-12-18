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
 char* INVPTR ; 
 scalar_t__ Isspace (char) ; 
 char QUOTE ; 
 scalar_t__ ismetahash (char) ; 

__attribute__((used)) static Char *
tw_tok(Char *str)
{
    static Char *bf = NULL;

    if (str != NULL)
	bf = str;
    
    /* skip leading spaces */
    for (; *bf && Isspace(*bf); bf++)
	continue;

    for (str = bf; *bf && !Isspace(*bf); bf++) {
	if (ismetahash(*bf))
	    return INVPTR;
	*bf = *bf & ~QUOTE;
    }
    if (*bf != '\0')
	*bf++ = '\0';

    return *str ? str : NULL;
}