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
 int /*<<< orphan*/  UChar (char) ; 
 int /*<<< orphan*/  failed (char*) ; 
 scalar_t__ isspace (int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *
stripped(char *src)
{
    char *dst = 0;

    while (isspace(UChar(*src)))
	src++;

    if (*src != '\0') {
	size_t len;

	if ((dst = strdup(src)) == NULL) {
	    failed("strdup");
	} else {
	    len = strlen(dst);
	    while (--len != 0 && isspace(UChar(dst[len])))
		dst[len] = '\0';
	}
    }
    return dst;
}