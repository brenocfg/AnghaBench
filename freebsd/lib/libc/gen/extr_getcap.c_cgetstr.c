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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ESC ; 
 size_t SFRAG ; 
 char* cgetcap (char*,char const*,char) ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (size_t) ; 
 char* reallocf (char*,size_t) ; 

int
cgetstr(char *buf, const char *cap, char **str)
{
	u_int m_room;
	char *bp, *mp;
	int len;
	char *mem;

	/*
	 * Find string capability cap
	 */
	bp = cgetcap(buf, cap, '=');
	if (bp == NULL)
		return (-1);

	/*
	 * Conversion / storage allocation loop ...  Allocate memory in
	 * chunks SFRAG in size.
	 */
	if ((mem = malloc(SFRAG)) == NULL) {
		errno = ENOMEM;
		return (-2);	/* couldn't even allocate the first fragment */
	}
	m_room = SFRAG;
	mp = mem;

	while (*bp != ':' && *bp != '\0') {
		/*
		 * Loop invariants:
		 *	There is always room for one more character in mem.
		 *	Mp always points just past last character in mem.
		 *	Bp always points at next character in buf.
		 */
		if (*bp == '^') {
			bp++;
			if (*bp == ':' || *bp == '\0')
				break;	/* drop unfinished escape */
			if (*bp == '?') {
				*mp++ = '\177';
				bp++;
			} else
				*mp++ = *bp++ & 037;
		} else if (*bp == '\\') {
			bp++;
			if (*bp == ':' || *bp == '\0')
				break;	/* drop unfinished escape */
			if ('0' <= *bp && *bp <= '7') {
				int n, i;

				n = 0;
				i = 3;	/* maximum of three octal digits */
				do {
					n = n * 8 + (*bp++ - '0');
				} while (--i && '0' <= *bp && *bp <= '7');
				*mp++ = n;
			}
			else switch (*bp++) {
				case 'b': case 'B':
					*mp++ = '\b';
					break;
				case 't': case 'T':
					*mp++ = '\t';
					break;
				case 'n': case 'N':
					*mp++ = '\n';
					break;
				case 'f': case 'F':
					*mp++ = '\f';
					break;
				case 'r': case 'R':
					*mp++ = '\r';
					break;
				case 'e': case 'E':
					*mp++ = ESC;
					break;
				case 'c': case 'C':
					*mp++ = ':';
					break;
				default:
					/*
					 * Catches '\', '^', and
					 *  everything else.
					 */
					*mp++ = *(bp-1);
					break;
			}
		} else
			*mp++ = *bp++;
		m_room--;

		/*
		 * Enforce loop invariant: if no room left in current
		 * buffer, try to get some more.
		 */
		if (m_room == 0) {
			size_t size = mp - mem;

			if ((mem = reallocf(mem, size + SFRAG)) == NULL)
				return (-2);
			m_room = SFRAG;
			mp = mem + size;
		}
	}
	*mp++ = '\0';	/* loop invariant let's us do this */
	m_room--;
	len = mp - mem - 1;

	/*
	 * Give back any extra memory and return value and success.
	 */
	if (m_room != 0)
		if ((mem = reallocf(mem, (size_t)(mp - mem))) == NULL)
			return (-2);
	*str = mem;
	return (len);
}