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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* xo_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
xo_strndup (const char *str, ssize_t len)
{
    if (len < 0)
	len = strlen(str);

    char *cp = xo_realloc(NULL, len + 1);
    if (cp) {
	memcpy(cp, str, len);
	cp[len] = '\0';
    }

    return cp;
}