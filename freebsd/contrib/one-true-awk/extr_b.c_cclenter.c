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
typedef  scalar_t__ uschar ;

/* Variables and functions */
 int /*<<< orphan*/  FATAL (char*,scalar_t__*) ; 
 int NCHARS ; 
 int /*<<< orphan*/  adjbuf (char**,int*,int,int,char**,char*) ; 
 scalar_t__ collate_range_cmp (int,int) ; 
 int /*<<< orphan*/  dprintf (char*) ; 
 scalar_t__ malloc (int) ; 
 int quoted (scalar_t__**) ; 
 scalar_t__ tostring (char*) ; 
 int /*<<< orphan*/  xfree (scalar_t__*) ; 

char *cclenter(const char *argp)	/* add a character class */
{
	int i, c, c2;
	int j;
	uschar *p = (uschar *) argp;
	uschar *op, *bp;
	static uschar *buf = NULL;
	static int bufsz = 100;

	op = p;
	if (buf == NULL && (buf = (uschar *) malloc(bufsz)) == NULL)
		FATAL("out of space for character class [%.10s...] 1", p);
	bp = buf;
	for (i = 0; (c = *p++) != 0; ) {
		if (c == '\\') {
			c = quoted(&p);
		} else if (c == '-' && i > 0 && bp[-1] != 0) {
			if (*p != 0) {
				c = bp[-1];
				c2 = *p++;
				if (c2 == '\\')
					c2 = quoted(&p);
				if (collate_range_cmp(c, c2) > 0) {
					bp--;
					i--;
					continue;
				}
				for (j = 0; j < NCHARS; j++) {
					if ((collate_range_cmp(c, j) > 0) ||
					    collate_range_cmp(j, c2) > 0)
						continue;
					if (!adjbuf((char **) &buf, &bufsz, bp-buf+2, 100, (char **) &bp, "cclenter1"))
						FATAL("out of space for character class [%.10s...] 2", p);
					*bp++ = j;
					i++;
				}
				continue;
			}
		}
		if (!adjbuf((char **) &buf, &bufsz, bp-buf+2, 100, (char **) &bp, "cclenter2"))
			FATAL("out of space for character class [%.10s...] 3", p);
		*bp++ = c;
		i++;
	}
	*bp = 0;
	dprintf( ("cclenter: in = |%s|, out = |%s|\n", op, buf) );
	xfree(op);
	return (char *) tostring((char *) buf);
}