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
 scalar_t__ EMPTYSTRING (char*) ; 
 int HEXTOINT (unsigned char) ; 
 scalar_t__ isxdigit (unsigned char) ; 

__attribute__((used)) static void
url_decode(char *url)
{
	unsigned char *p, *q;

	if (EMPTYSTRING(url))
		return;
	p = q = (unsigned char *)url;

#define	HEXTOINT(x) (x - (isdigit(x) ? '0' : (islower(x) ? 'a' : 'A') - 10))
	while (*p) {
		if (p[0] == '%'
		    && p[1] && isxdigit((unsigned char)p[1])
		    && p[2] && isxdigit((unsigned char)p[2])) {
			*q++ = HEXTOINT(p[1]) * 16 + HEXTOINT(p[2]);
			p+=3;
		} else
			*q++ = *p++;
	}
	*q = '\0';
}