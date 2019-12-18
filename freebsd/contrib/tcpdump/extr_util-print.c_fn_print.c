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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_ISASCII (char) ; 
 int /*<<< orphan*/  ND_ISPRINT (char) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 char ND_TOASCII (char) ; 

int
fn_print(netdissect_options *ndo,
         register const u_char *s, register const u_char *ep)
{
	register int ret;
	register u_char c;

	ret = 1;			/* assume truncated */
	while (ep == NULL || s < ep) {
		c = *s++;
		if (c == '\0') {
			ret = 0;
			break;
		}
		if (!ND_ISASCII(c)) {
			c = ND_TOASCII(c);
			ND_PRINT((ndo, "M-"));
		}
		if (!ND_ISPRINT(c)) {
			c ^= 0x40;	/* DEL to ?, others to alpha */
			ND_PRINT((ndo, "^"));
		}
		ND_PRINT((ndo, "%c", c));
	}
	return(ret);
}