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
 char const TRIM ; 
 scalar_t__ samecase (char const) ; 

int
StrQcmp(const Char *str1, const Char *str2)
{
    for (; *str1 && samecase(*str1 & TRIM) == samecase(*str2 & TRIM); 
	 str1++, str2++)
	continue;
    /*
     * The following case analysis is necessary so that characters which look
     * negative collate low against normal characters but high against the
     * end-of-string NUL.
     */
    if (*str1 == '\0' && *str2 == '\0')
	return (0);
    else if (*str1 == '\0')
	return (-1);
    else if (*str2 == '\0')
	return (1);
    else
	return ((*str1 & TRIM) - (*str2 & TRIM));
}