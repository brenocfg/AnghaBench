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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  _key ;

/* Variables and functions */
 char* _warc_find_eol (char const*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 long strtol (char const*,char**,int) ; 
 char* xmemmem (char const*,size_t,char const*,int) ; 

__attribute__((used)) static ssize_t
_warc_rdlen(const char *buf, size_t bsz)
{
	static const char _key[] = "\r\nContent-Length:";
	const char *val, *eol;
	char *on = NULL;
	long int len;

	if ((val = xmemmem(buf, bsz, _key, sizeof(_key) - 1U)) == NULL) {
		/* no bother */
		return -1;
	}
	val += sizeof(_key) - 1U;
	if ((eol = _warc_find_eol(val, buf + bsz - val)) == NULL) {
		/* no end of line */
		return -1;
	}

	/* skip leading whitespace */
	while (val < eol && (*val == ' ' || *val == '\t'))
		val++;
	/* there must be at least one digit */
	if (!isdigit((unsigned char)*val))
		return -1;
	errno = 0;
	len = strtol(val, &on, 10);
	if (errno != 0 || on != eol) {
		/* line must end here */
		return -1;
	}

	return (size_t)len;
}