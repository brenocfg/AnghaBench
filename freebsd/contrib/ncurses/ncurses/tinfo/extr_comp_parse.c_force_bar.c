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
 size_t MAX_NAME_SIZE ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,size_t) ; 
 scalar_t__ strchr (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static char *
force_bar(char *dst, char *src)
{
    if (strchr(src, '|') == 0) {
	size_t len = strlen(src);
	if (len > MAX_NAME_SIZE)
	    len = MAX_NAME_SIZE;
	(void) strncpy(dst, src, len);
	_nc_STRCPY(dst + len, "|", MAX_NAME_SIZE);
	src = dst;
    }
    return src;
}