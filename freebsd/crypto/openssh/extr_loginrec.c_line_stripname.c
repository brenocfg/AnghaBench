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
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

char *
line_stripname(char *dst, const char *src, int dstsize)
{
	memset(dst, '\0', dstsize);
	if (strncmp(src, "/dev/", 5) == 0)
		strlcpy(dst, src + 5, dstsize);
	else
		strlcpy(dst, src, dstsize);
	return (dst);
}