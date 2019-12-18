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
typedef  int /*<<< orphan*/  optbuf ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,unsigned int) ; 
 int /*<<< orphan*/  isascii (unsigned char) ; 
 int /*<<< orphan*/  isprint (unsigned char) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char) ; 
 int /*<<< orphan*/  warning (char*) ; 

const char *
option_as_string(unsigned int code, unsigned char *data, int len)
{
	static char optbuf[32768]; /* XXX */
	char *op = optbuf;
	int opleft = sizeof(optbuf);
	unsigned char *dp = data;

	if (code > 255)
		error("option_as_string: bad code %d", code);

	for (; dp < data + len; dp++) {
		if (!isascii(*dp) || !isprint(*dp)) {
			if (dp + 1 != data + len || *dp != 0) {
				snprintf(op, opleft, "\\%03o", *dp);
				op += 4;
				opleft -= 4;
			}
		} else if (*dp == '"' || *dp == '\'' || *dp == '$' ||
		    *dp == '`' || *dp == '\\') {
			*op++ = '\\';
			*op++ = *dp;
			opleft -= 2;
		} else {
			*op++ = *dp;
			opleft--;
		}
	}
	if (opleft < 1)
		goto toobig;
	*op = 0;
	return optbuf;
toobig:
	warning("dhcp option too large");
	return "<error>";
}