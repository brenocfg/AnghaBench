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
typedef  char u_int8_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  isxdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strchr (char const*,char const) ; 
 int tohex (int /*<<< orphan*/ ) ; 
 char tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static const char *
get_string(const char *val, const char *sep, u_int8_t *buf, int *lenp)
{
	int len;
	int hexstr;
	u_int8_t *p;

	len = *lenp;
	p = buf;
	hexstr = (val[0] == '0' && tolower((u_char)val[1]) == 'x');
	if (hexstr)
		val += 2;
	for (;;) {
		if (*val == '\0')
			break;
		if (sep != NULL && strchr(sep, *val) != NULL) {
			val++;
			break;
		}
		if (hexstr) {
			if (!isxdigit((u_char)val[0])) {
				warnx("bad hexadecimal digits");
				return NULL;
			}
			if (!isxdigit((u_char)val[1])) {
				warnx("odd count hexadecimal digits");
				return NULL;
			}
		}
		if (p >= buf + len) {
			if (hexstr)
				warnx("hexadecimal digits too long");
			else
				warnx("string too long");
			return NULL;
		}
		if (hexstr) {
#define	tohex(x)	(isdigit(x) ? (x) - '0' : tolower(x) - 'a' + 10)
			*p++ = (tohex((u_char)val[0]) << 4) |
			    tohex((u_char)val[1]);
#undef tohex
			val += 2;
		} else
			*p++ = *val++;
	}
	len = p - buf;
	/* The string "-" is treated as the empty string. */
	if (!hexstr && len == 1 && buf[0] == '-') {
		len = 0;
		memset(buf, 0, *lenp);
	} else if (len < *lenp)
		memset(p, 0, *lenp - len);
	*lenp = len;
	return val;
}