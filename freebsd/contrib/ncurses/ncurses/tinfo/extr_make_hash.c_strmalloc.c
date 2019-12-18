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
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,size_t) ; 
 int /*<<< orphan*/  failed (char*) ; 
 char* malloc (size_t) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
strmalloc(char *s)
{
    size_t need = strlen(s) + 1;
    char *result = malloc(need);
    if (result == 0)
	failed("strmalloc");
    _nc_STRCPY(result, s, need);
    return result;
}