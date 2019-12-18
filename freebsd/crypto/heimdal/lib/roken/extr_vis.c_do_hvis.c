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
 char* do_svis (char*,int,int,int,char const*) ; 
 int /*<<< orphan*/  isalnum (int) ; 
 int /*<<< orphan*/  isascii (int) ; 
 int /*<<< orphan*/ * strchr (char*,int) ; 
 void* xtoa (unsigned int) ; 

__attribute__((used)) static char *
do_hvis(char *dst, int c, int flag, int nextc, const char *extra)
{
	if (!isascii(c) || !isalnum(c) || strchr("$-_.+!*'(),", c) != NULL) {
		*dst++ = '%';
		*dst++ = xtoa(((unsigned int)c >> 4) & 0xf);
		*dst++ = xtoa((unsigned int)c & 0xf);
	} else {
		dst = do_svis(dst, c, flag, nextc, extra);
	}
	return dst;
}