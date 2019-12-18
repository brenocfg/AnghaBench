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
 int errno ; 
 char* realloc (char*,int) ; 
 char* reallocarray (int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int strvis (char*,char const*,int) ; 

int
stravis(char **outp, const char *src, int flag)
{
	char *buf;
	int len, serrno;

	buf = reallocarray(NULL, 4, strlen(src) + 1);
	if (buf == NULL)
		return -1;
	len = strvis(buf, src, flag);
	serrno = errno;
	*outp = realloc(buf, len + 1);
	if (*outp == NULL) {
		*outp = buf;
		errno = serrno;
	}
	return (len);
}