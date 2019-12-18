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
 int strlen (char*) ; 

char *strrev( char *string )    
{                               /* reverse a string in-place */
    int i = strlen(string);
    char *p1 = string;          /* first char of string */
    char *p2 = string + i - 1;  /* last non-NULL char of string */
    char c;

    if (i > 1)
    {
        while (p1 < p2)
        {
            c = *p2;
            *p2 = *p1;
            *p1 = c;
            p1++; p2--;
        }
    }
        
    return string;
}