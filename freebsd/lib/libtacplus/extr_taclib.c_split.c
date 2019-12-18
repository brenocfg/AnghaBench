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
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 int /*<<< orphan*/  strcspn (char*,char const*) ; 
 scalar_t__ strspn (char*,char const*) ; 

__attribute__((used)) static int
split(char *str, char *fields[], int maxfields, char *msg, size_t msglen)
{
	char *p;
	int i;
	static const char ws[] = " \t";

	for (i = 0;  i < maxfields;  i++)
		fields[i] = NULL;
	p = str;
	i = 0;
	while (*p != '\0') {
		p += strspn(p, ws);
		if (*p == '#' || *p == '\0')
			break;
		if (i >= maxfields) {
			snprintf(msg, msglen, "line has too many fields");
			return -1;
		}
		if (*p == '"') {
			char *dst;

			dst = ++p;
			fields[i] = dst;
			while (*p != '"') {
				if (*p == '\\') {
					p++;
					if (*p != '"' && *p != '\\' &&
					    *p != '\0') {
						snprintf(msg, msglen,
						    "invalid `\\' escape");
						return -1;
					}
				}
				if (*p == '\0') {
					snprintf(msg, msglen,
					    "unterminated quoted string");
					return -1;
				}
				*dst++ = *p++;
			}
			*dst = '\0';
			p++;
			if (*p != '\0' && strspn(p, ws) == 0) {
				snprintf(msg, msglen, "quoted string not"
				    " followed by white space");
				return -1;
			}
		} else {
			fields[i] = p;
			p += strcspn(p, ws);
			if (*p != '\0')
				*p++ = '\0';
		}
		i++;
	}
	return i;
}