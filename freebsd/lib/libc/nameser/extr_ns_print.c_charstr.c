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
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 scalar_t__ addstr (char const*,int,char**,size_t*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * strchr (char*,int const) ; 

__attribute__((used)) static int
charstr(const u_char *rdata, const u_char *edata, char **buf, size_t *buflen) {
	const u_char *odata = rdata;
	size_t save_buflen = *buflen;
	char *save_buf = *buf;

	if (addstr("\"", 1, buf, buflen) < 0)
		goto enospc;
	if (rdata < edata) {
		int n = *rdata;

		if (rdata + 1 + n <= edata) {
			rdata++;
			while (n-- > 0) {
				if (strchr("\n\"\\", *rdata) != NULL)
					if (addstr("\\", 1, buf, buflen) < 0)
						goto enospc;
				if (addstr((const char *)rdata, 1,
					   buf, buflen) < 0)
					goto enospc;
				rdata++;
			}
		}
	}
	if (addstr("\"", 1, buf, buflen) < 0)
		goto enospc;
	return (rdata - odata);
 enospc:
	errno = ENOSPC;
	*buf = save_buf;
	*buflen = save_buflen;
	return (-1);
}