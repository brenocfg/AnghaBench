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
 char** allocarray (int) ; 
 char* allocstr (char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int strcspn (char const*,char const*) ; 

__attribute__((used)) static const char **
arrayize(const char *str, const char *chars, int *size)
{
    int	    i;
    char *ptr;
    const char *cptr;
    const char **res = NULL;

    /* count the sub-strings */
    for (i = 0, cptr = str; *cptr; i++) {
	int count = strcspn(cptr, chars);
	cptr += count;
	if (*cptr)
	    ++cptr;
    }

    /* alloc the array */
    if ((ptr = allocstr(str)) != NULL) {
	if ((res = allocarray(++i)) == NULL)
	    free((void *)(uintptr_t)(const void *)str);
	else {
	    /* now split the string */
	    i = 0;
	    while (*ptr) {
		int count = strcspn(ptr, chars);
		res[i++] = ptr;
		ptr += count;
		if (*ptr)
		    *ptr++ = '\0';
	    }
	    res[i] = NULL;
	}
    }

    if (size)
	*size = i;

    return res;
}