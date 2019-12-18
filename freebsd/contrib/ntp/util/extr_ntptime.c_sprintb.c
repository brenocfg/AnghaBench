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
typedef  int u_int ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 

const char *
sprintb(
	u_int		v,
	const char *	bits
	)
{
	char *cp;
	char *cplim;
	int i;
	int any;
	char c;
	static char buf[132];

	if (bits != NULL && *bits == 8)
		snprintf(buf, sizeof(buf), "0%o", v);
	else
		snprintf(buf, sizeof(buf), "0x%x", v);
	cp = buf + strlen(buf);
	cplim = buf + sizeof(buf);
	if (bits != NULL) {
		bits++;
		*cp++ = ' ';
		*cp++ = '(';
		any = FALSE;
		while ((i = *bits++) != 0) {
			if (v & (1 << (i - 1))) {
				if (any) {
					*cp++ = ',';
					if (cp >= cplim)
						goto overrun;
				}
				any = TRUE;
				for (; (c = *bits) > 32; bits++) {
					*cp++ = c;
					if (cp >= cplim)
						goto overrun;
				}
			} else {
				for (; *bits > 32; bits++)
					continue;
			}
		}
		*cp++ = ')';
		if (cp >= cplim)
			goto overrun;
	}
	*cp = '\0';
	return buf;

    overrun:
	return "sprintb buffer too small";
}