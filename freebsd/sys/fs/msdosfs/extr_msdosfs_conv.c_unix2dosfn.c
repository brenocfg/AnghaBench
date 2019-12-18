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
typedef  int uint16_t ;
typedef  int u_int ;
typedef  char u_char ;
struct msdosfsmount {int /*<<< orphan*/  pm_d2u; int /*<<< orphan*/  pm_flags; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  gentext ;

/* Variables and functions */
 char SLOT_E5 ; 
 scalar_t__ mbsadjpos (char const**,int,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unix2doschr (char const**,...) ; 

int
unix2dosfn(const u_char *un, u_char dn[12], size_t unlen, u_int gen,
    struct msdosfsmount *pmp)
{
	ssize_t i, j;
	int l;
	int conv = 1;
	const u_char *cp, *dp, *dp1;
	u_char gentext[6], *wcp;
	uint16_t c;

	/*
	 * Fill the dos filename string with blanks. These are DOS's pad
	 * characters.
	 */
	for (i = 0; i < 11; i++)
		dn[i] = ' ';
	dn[11] = 0;

	/*
	 * The filenames "." and ".." are handled specially, since they
	 * don't follow dos filename rules.
	 */
	if (un[0] == '.' && unlen == 1) {
		dn[0] = '.';
		return gen <= 1;
	}
	if (un[0] == '.' && un[1] == '.' && unlen == 2) {
		dn[0] = '.';
		dn[1] = '.';
		return gen <= 1;
	}

	/*
	 * Filenames with only blanks and dots are not allowed!
	 */
	for (cp = un, i = unlen; --i >= 0; cp++)
		if (*cp != ' ' && *cp != '.')
			break;
	if (i < 0)
		return 0;


	/*
	 * Filenames with some characters are not allowed!
	 */
	for (cp = un, i = unlen; i > 0;)
		if (unix2doschr(&cp, (size_t *)&i, pmp) == 0)
			return 0;

	/*
	 * Now find the extension
	 * Note: dot as first char doesn't start extension
	 *	 and trailing dots and blanks are ignored
	 * Note(2003/7): It seems recent Windows has
	 *	 defferent rule than this code, that Windows
	 *	 ignores all dots before extension, and use all
	 *	 chars as filename except for dots.
	 */
	dp = dp1 = NULL;
	for (cp = un + 1, i = unlen - 1; --i >= 0;) {
		switch (*cp++) {
		case '.':
			if (!dp1)
				dp1 = cp;
			break;
		case ' ':
			break;
		default:
			if (dp1)
				dp = dp1;
			dp1 = NULL;
			break;
		}
	}

	/*
	 * Now convert it (this part is for extension).
	 * As Windows XP do, if it's not ascii char,
	 * this function should return 2 or 3, so that checkng out Unicode name.
	 */
	if (dp) {
		if (dp1)
			l = dp1 - dp;
		else
			l = unlen - (dp - un);
		for (cp = dp, i = l, j = 8; i > 0 && j < 11; j++) {
			c = unix2doschr(&cp, (size_t *)&i, pmp);
			if (c & 0xff00) {
				dn[j] = c >> 8;
				if (++j < 11) {
					dn[j] = c;
					if (conv != 3)
						conv = 2;
					continue;
				} else {
					conv = 3;
					dn[j-1] = ' ';
					break;
				}
			} else {
				dn[j] = c;
			}
			if (((dn[j] & 0x80) || *(cp - 1) != dn[j]) && conv != 3)
				conv = 2;
			if (dn[j] == 1) {
				conv = 3;
				dn[j] = '_';
			}
			if (dn[j] == 2) {
				conv = 3;
				dn[j--] = ' ';
			}
		}
		if (i > 0)
			conv = 3;
		dp--;
	} else {
		for (dp = cp; *--dp == ' ' || *dp == '.';);
		dp++;
	}

	/*
	 * Now convert the rest of the name
	 */
	for (i = dp - un, j = 0; un < dp && j < 8; j++) {
		c = unix2doschr(&un, &i, pmp);
		if (c & 0xff00) {
			dn[j] = c >> 8;
			if (++j < 8) {
				dn[j] = c;
				if (conv != 3)
					conv = 2;
				continue;
			} else {
				conv = 3;
				dn[j-1] = ' ';
				break;
			}
		} else {
			dn[j] = c;
		}
		if (((dn[j] & 0x80) || *(un - 1) != dn[j]) && conv != 3)
			conv = 2;
		if (dn[j] == 1) {
			conv = 3;
			dn[j] = '_';
		}
		if (dn[j] == 2) {
			conv = 3;
			dn[j--] = ' ';
		}
	}
	if (un < dp)
		conv = 3;
	/*
	 * If we didn't have any chars in filename,
	 * generate a default
	 */
	if (!j)
		dn[0] = '_';

	/*
	 * If there wasn't any char dropped,
	 * there is no place for generation numbers
	 */
	if (conv != 3) {
		if (gen > 1)
			conv = 0;
		goto done;
	}

	/*
	 * Now insert the generation number into the filename part
	 */
	if (gen == 0)
		goto done;
	for (wcp = gentext + sizeof(gentext); wcp > gentext && gen; gen /= 10)
		*--wcp = gen % 10 + '0';
	if (gen) {
		conv = 0;
		goto done;
	}
	for (i = 8; dn[--i] == ' ';);
	i++;
	if (gentext + sizeof(gentext) - wcp + 1 > 8 - i)
		i = 8 - (gentext + sizeof(gentext) - wcp + 1);
	/*
	 * Correct posision to where insert the generation number
	 */
	cp = dn;
	i -= mbsadjpos((const char**)&cp, i, unlen, 1, pmp->pm_flags, pmp->pm_d2u);

	dn[i++] = '~';
	while (wcp < gentext + sizeof(gentext))
		dn[i++] = *wcp++;

	/*
	 * Tail of the filename should be space
	 */
	while (i < 8)
		dn[i++] = ' ';
	conv = 3;

done:
	/*
	 * The first character cannot be E5,
	 * because that means a deleted entry
	 */
	if (dn[0] == 0xe5)
		dn[0] = SLOT_E5;

	return conv;
}