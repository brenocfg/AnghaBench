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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ noctfix ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static const char*
ctf(const char *fmt) {
	static char  buf[31];
	const char  *src, *end;
	char	    *dst;

	if (noctfix)
		return (fmt);

	end = buf + sizeof(buf);
	for (src = fmt, dst = buf; dst < end; *dst++ = *src++) {
		if (*src == '\0') {
			*dst = '\0';
			break;
		} else if (*src == '%' && *(src+1) == 's') {
			*dst++ = '%';
			*dst++ = 'h';
			*dst++ = 's';
			strlcpy(dst, src+2, end - dst);
			return (buf);
		}
	}
	return (buf);
}