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
 int /*<<< orphan*/  free (char*) ; 
 int hexchar (char const*) ; 
 int /*<<< orphan*/  isxdigit (unsigned char) ; 
 scalar_t__ strlen (char const*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static char *
urldecode(const char *src)
{
	char *ret, *dst;
	int ch;

	ret = xmalloc(strlen(src) + 1);
	for (dst = ret; *src != '\0'; src++) {
		switch (*src) {
		case '+':
			*dst++ = ' ';
			break;
		case '%':
			if (!isxdigit((unsigned char)src[1]) ||
			    !isxdigit((unsigned char)src[2]) ||
			    (ch = hexchar(src + 1)) == -1) {
				free(ret);
				return NULL;
			}
			*dst++ = ch;
			src += 2;
			break;
		default:
			*dst++ = *src;
			break;
		}
	}
	*dst = '\0';

	return ret;
}