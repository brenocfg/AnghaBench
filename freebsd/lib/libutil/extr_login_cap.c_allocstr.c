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
 char* internal_string ; 
 size_t internal_stringsz ; 
 char* realloc (char*,size_t) ; 
 char* strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
allocstr(const char *str)
{
    char    *p;

    size_t sz = strlen(str) + 1;	/* realloc() only if necessary */
    if (sz <= internal_stringsz)
	p = strcpy(internal_string, str);
    else if ((p = realloc(internal_string, sz)) != NULL) {
	internal_stringsz = sz;
	internal_string = strcpy(p, str);
    }
    return p;
}