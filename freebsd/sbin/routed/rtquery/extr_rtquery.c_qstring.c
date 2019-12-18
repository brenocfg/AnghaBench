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
typedef  char u_char ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static char *
qstring(u_char *s, int len)
{
	static char buf[8*20+1];
	char *p;
	u_char *s2, c;


	for (p = buf; len != 0 && p < &buf[sizeof(buf)-1]; len--) {
		c = *s++;
		if (c == '\0') {
			for (s2 = s+1; s2 < &s[len]; s2++) {
				if (*s2 != '\0')
					break;
			}
			if (s2 >= &s[len])
			    goto exit;
		}

		if (c >= ' ' && c < 0x7f && c != '\\') {
			*p++ = c;
			continue;
		}
		*p++ = '\\';
		switch (c) {
		case '\\':
			*p++ = '\\';
			break;
		case '\n':
			*p++= 'n';
			break;
		case '\r':
			*p++= 'r';
			break;
		case '\t':
			*p++ = 't';
			break;
		case '\b':
			*p++ = 'b';
			break;
		default:
			p += sprintf(p,"%o",c);
			break;
		}
	}
exit:
	*p = '\0';
	return buf;
}