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
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 char* mapin ; 
 char* mapout ; 
 int /*<<< orphan*/  ttyout ; 

__attribute__((used)) static const char *
domap(char *dst, size_t dlen, const char *src)
{
	const char *cp1 = src;
	char *cp2 = mapin;
	const char *tp[9], *te[9];
	int i, toks[9], toknum = 0, match = 1;

	for (i=0; i < 9; ++i) {
		toks[i] = 0;
	}
	while (match && *cp1 && *cp2) {
		switch (*cp2) {
			case '\\':
				if (*++cp2 != *cp1) {
					match = 0;
				}
				break;
			case '$':
				if (*(cp2+1) >= '1' && (*cp2+1) <= '9') {
					if (*cp1 != *(++cp2+1)) {
						toks[toknum = *cp2 - '1']++;
						tp[toknum] = cp1;
						while (*++cp1 && *(cp2+1)
							!= *cp1);
						te[toknum] = cp1;
					}
					cp2++;
					break;
				}
				/* FALLTHROUGH */
			default:
				if (*cp2 != *cp1) {
					match = 0;
				}
				break;
		}
		if (match && *cp1) {
			cp1++;
		}
		if (match && *cp2) {
			cp2++;
		}
	}
	if (!match && *cp1) /* last token mismatch */
	{
		toks[toknum] = 0;
	}
	cp2 = dst;
	*cp2 = '\0';
	cp1 = mapout;
	while (*cp1) {
		match = 0;
		switch (*cp1) {
			case '\\':
				if (*(cp1 + 1)) {
					*cp2++ = *++cp1;
				}
				break;
			case '[':
LOOP:
				if (*++cp1 == '$' &&
				    isdigit((unsigned char)*(cp1+1))) {
					if (*++cp1 == '0') {
						const char *cp3 = src;

						while (*cp3) {
							*cp2++ = *cp3++;
						}
						match = 1;
					}
					else if (toks[toknum = *cp1 - '1']) {
						const char *cp3 = tp[toknum];

						while (cp3 != te[toknum]) {
							*cp2++ = *cp3++;
						}
						match = 1;
					}
				}
				else {
					while (*cp1 && *cp1 != ',' &&
					    *cp1 != ']') {
						if (*cp1 == '\\') {
							cp1++;
						}
						else if (*cp1 == '$' &&
						    isdigit((unsigned char)*(cp1+1))) {
							if (*++cp1 == '0') {
							   const char *cp3 = src;

							   while (*cp3) {
								*cp2++ = *cp3++;
							   }
							}
							else if (toks[toknum =
							    *cp1 - '1']) {
							   const char *cp3=tp[toknum];

							   while (cp3 !=
								  te[toknum]) {
								*cp2++ = *cp3++;
							   }
							}
						}
						else if (*cp1) {
							*cp2++ = *cp1++;
						}
					}
					if (!*cp1) {
						fputs(
						"nmap: unbalanced brackets.\n",
						    ttyout);
						return (src);
					}
					match = 1;
					cp1--;
				}
				if (match) {
					while (*++cp1 && *cp1 != ']') {
					      if (*cp1 == '\\' && *(cp1 + 1)) {
							cp1++;
					      }
					}
					if (!*cp1) {
						fputs(
						"nmap: unbalanced brackets.\n",
						    ttyout);
						return (src);
					}
					break;
				}
				switch (*++cp1) {
					case ',':
						goto LOOP;
					case ']':
						break;
					default:
						cp1--;
						goto LOOP;
				}
				break;
			case '$':
				if (isdigit((unsigned char)*(cp1 + 1))) {
					if (*++cp1 == '0') {
						const char *cp3 = src;

						while (*cp3) {
							*cp2++ = *cp3++;
						}
					}
					else if (toks[toknum = *cp1 - '1']) {
						const char *cp3 = tp[toknum];

						while (cp3 != te[toknum]) {
							*cp2++ = *cp3++;
						}
					}
					break;
				}
				/* intentional drop through */
			default:
				*cp2++ = *cp1;
				break;
		}
		cp1++;
	}
	*cp2 = '\0';
	return *dst ? dst : src;
}