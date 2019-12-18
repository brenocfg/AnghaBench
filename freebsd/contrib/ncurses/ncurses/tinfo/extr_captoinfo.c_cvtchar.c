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
 int /*<<< orphan*/  UChar (char const) ; 
 int /*<<< orphan*/  dp ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 scalar_t__ isgraph (unsigned char) ; 
 int /*<<< orphan*/  save_char (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  save_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cvtchar(register const char *sp)
/* convert a character to a terminfo push */
{
    unsigned char c = 0;
    int len;

    switch (*sp) {
    case '\\':
	switch (*++sp) {
	case '\'':
	case '$':
	case '\\':
	case '%':
	    c = (unsigned char) (*sp);
	    len = 2;
	    break;
	case '\0':
	    c = '\\';
	    len = 1;
	    break;
	case '0':
	case '1':
	case '2':
	case '3':
	    len = 1;
	    while (isdigit(UChar(*sp))) {
		c = (unsigned char) (8 * c + (*sp++ - '0'));
		len++;
	    }
	    break;
	default:
	    c = (unsigned char) (*sp);
	    len = 2;
	    break;
	}
	break;
    case '^':
	c = (unsigned char) (*++sp & 0x1f);
	len = 2;
	break;
    default:
	c = (unsigned char) (*sp);
	len = 1;
    }
    if (isgraph(c) && c != ',' && c != '\'' && c != '\\' && c != ':') {
	dp = save_string(dp, "%\'");
	dp = save_char(dp, c);
	dp = save_char(dp, '\'');
    } else {
	dp = save_string(dp, "%{");
	if (c > 99)
	    dp = save_char(dp, c / 100 + '0');
	if (c > 9)
	    dp = save_char(dp, ((int) (c / 10)) % 10 + '0');
	dp = save_char(dp, c % 10 + '0');
	dp = save_char(dp, '}');
    }
    return len;
}