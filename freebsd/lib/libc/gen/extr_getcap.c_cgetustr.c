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
 size_t SFRAG ; 
 char* cgetcap (char*,char const*,char) ; 
 int /*<<< orphan*/  errno ; 
 char* malloc (size_t) ; 
 char* reallocf (char*,size_t) ; 

int
cgetustr(char *buf, const char *cap, char **str)
{
	u_int m_room;
	char *bp, *mp;
	int len;
	char *mem;

	/*
	 * Find string capability cap
	 */
	if ((bp = cgetcap(buf, cap, '=')) == NULL)
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