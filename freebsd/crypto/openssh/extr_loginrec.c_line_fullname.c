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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  memset (char*,char,scalar_t__) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

char *
line_fullname(char *dst, const char *src, u_int dstsize)
{
	memset(dst, '\0', dstsize);
	if ((strncmp(src, "/dev/", 5) == 0) || (dstsize < (strlen(src) + 5)))
		strlcpy(dst, src, dstsize);
	else {
		strlcpy(dst, "/dev/", dstsize);
		strlcat(dst, src, dstsize);
	}
	return (dst);
}