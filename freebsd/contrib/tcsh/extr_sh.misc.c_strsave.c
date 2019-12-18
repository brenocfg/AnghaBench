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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 
 char* xmalloc (size_t) ; 

char   *
strsave(const char *s)
{
    char   *r;
    size_t size;

    if (s == NULL)
	s = "";
    size = strlen(s) + 1;
    r = xmalloc(size);
    memcpy(r, s, size);
    return (r);
}