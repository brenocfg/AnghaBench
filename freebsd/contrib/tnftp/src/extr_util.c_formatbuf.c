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
 int /*<<< orphan*/  ADDBUF (char const) ; 
 int /*<<< orphan*/  connected ; 
 char* hostname ; 
 char* remotecwd ; 
 char* username ; 

void
formatbuf(char *buf, size_t len, const char *src)
{
	const char	*p, *p2, *q;
	size_t		 i;
	int		 op, updirs, pdirs;

#define ADDBUF(x) do { \
		if (i >= len - 1) \
			goto endbuf; \
		buf[i++] = (x); \
	} while (0)

	p = src;
	for (i = 0; *p; p++) {
		if (*p != '%') {
			ADDBUF(*p);
			continue;
		}
		p++;

		switch (op = *p) {

		case '/':
		case '.':
		case 'c':
			p2 = connected ? remotecwd : "";
			updirs = pdirs = 0;

			/* option to determine fixed # of dirs from path */
			if (op == '.' || op == 'c') {
				int skip;

				q = p2;
				while (*p2)		/* calc # of /'s */
					if (*p2++ == '/')
						updirs++;
				if (p[1] == '0') {	/* print <x> or ... */
					pdirs = 1;
					p++;
				}
				if (p[1] >= '1' && p[1] <= '9') {
							/* calc # to skip  */
					skip = p[1] - '0';
					p++;
				} else
					skip = 1;

				updirs -= skip;
				while (skip-- > 0) {
					while ((p2 > q) && (*p2 != '/'))
						p2--;	/* back up */
					if (skip && p2 > q)
						p2--;
				}
				if (*p2 == '/' && p2 != q)
					p2++;
			}

			if (updirs > 0 && pdirs) {
				if (i >= len - 5)
					break;
				if (op == '.') {
					ADDBUF('.');
					ADDBUF('.');
					ADDBUF('.');
				} else {
					ADDBUF('/');
					ADDBUF('<');
					if (updirs > 9) {
						ADDBUF('9');
						ADDBUF('+');
					} else
						ADDBUF('0' + updirs);
					ADDBUF('>');
				}
			}
			for (; *p2; p2++)
				ADDBUF(*p2);
			break;

		case 'M':
		case 'm':
			for (p2 = connected && hostname ? hostname : "-";
			    *p2 ; p2++) {
				if (op == 'm' && *p2 == '.')
					break;
				ADDBUF(*p2);
			}
			break;

		case 'n':
			for (p2 = connected ? username : "-"; *p2 ; p2++)
				ADDBUF(*p2);
			break;

		case '%':
			ADDBUF('%');
			break;

		default:		/* display unknown codes literally */
			ADDBUF('%');
			ADDBUF(op);
			break;

		}
	}
 endbuf:
	buf[i] = '\0';
}