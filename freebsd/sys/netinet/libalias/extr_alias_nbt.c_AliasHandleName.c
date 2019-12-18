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
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ isprint (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static u_char  *
AliasHandleName(u_char * p, char *pmax)
{

	u_char *s;
	u_char c;
	int compress;

	/* Following length field */

	if (p == NULL || (char *)p >= pmax)
		return (NULL);

	if (*p & 0xc0) {
		p = p + 2;
		if ((char *)p > pmax)
			return (NULL);
		return ((u_char *) p);
	}
	while ((*p & 0x3f) != 0x00) {
		s = p + 1;
		if (*p == 0x20)
			compress = 1;
		else
			compress = 0;

		/* Get next length field */
		p = (u_char *) (p + (*p & 0x3f) + 1);
		if ((char *)p > pmax) {
			p = NULL;
			break;
		}
#ifdef LIBALIAS_DEBUG
		printf(":");
#endif
		while (s < p) {
			if (compress == 1) {
				c = (u_char) (((((*s & 0x0f) << 4) | (*(s + 1) & 0x0f)) - 0x11));
#ifdef LIBALIAS_DEBUG
				if (isprint(c))
					printf("%c", c);
				else
					printf("<0x%02x>", c);
#endif
				s += 2;
			} else {
#ifdef LIBALIAS_DEBUG
				printf("%c", *s);
#endif
				s++;
			}
		}
#ifdef LIBALIAS_DEBUG
		printf(":");
		fflush(stdout);
#endif
	}

	/* Set up to out of Name field */
	if (p == NULL || (char *)p >= pmax)
		p = NULL;
	else
		p++;
	return ((u_char *) p);
}