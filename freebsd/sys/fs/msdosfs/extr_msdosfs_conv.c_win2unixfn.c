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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  char u_char ;
struct winentry {int weCnt; int weChksum; int* wePart1; int* wePart2; int* wePart3; } ;
struct msdosfsmount {int dummy; } ;
struct mbnambuf {int dummy; } ;

/* Variables and functions */
 int WIN_CHARS ; 
 int WIN_CNT ; 
 int WIN_LAST ; 
 int /*<<< orphan*/  WIN_MAXLEN ; 
 int howmany (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mbnambuf_write (struct mbnambuf*,int*,int) ; 
 char* win2unixchr (char*,int,struct msdosfsmount*) ; 

int
win2unixfn(struct mbnambuf *nbp, struct winentry *wep, int chksum,
    struct msdosfsmount *pmp)
{
	u_char *c, tmpbuf[5];
	uint8_t *cp;
	uint8_t *np, name[WIN_CHARS * 3 + 1];
	uint16_t code;
	int i;

	if ((wep->weCnt&WIN_CNT) > howmany(WIN_MAXLEN, WIN_CHARS)
	    || !(wep->weCnt&WIN_CNT))
		return -1;

	/*
	 * First compare checksums
	 */
	if (wep->weCnt&WIN_LAST) {
		chksum = wep->weChksum;
	} else if (chksum != wep->weChksum)
		chksum = -1;
	if (chksum == -1)
		return -1;

	/*
	 * Convert the name parts
	 */
	np = name;
	for (cp = wep->wePart1, i = sizeof(wep->wePart1)/2; --i >= 0;) {
		code = (cp[1] << 8) | cp[0];
		switch (code) {
		case 0:
			*np = '\0';
			if (mbnambuf_write(nbp, name,
			    (wep->weCnt & WIN_CNT) - 1) != 0)
				return -1;
			return chksum;
		case '/':
			*np = '\0';
			return -1;
		default:
			c = win2unixchr(tmpbuf, code, pmp);
			while (*c != '\0')
				*np++ = *c++;
			break;
		}
		cp += 2;
	}
	for (cp = wep->wePart2, i = sizeof(wep->wePart2)/2; --i >= 0;) {
		code = (cp[1] << 8) | cp[0];
		switch (code) {
		case 0:
			*np = '\0';
			if (mbnambuf_write(nbp, name,
			    (wep->weCnt & WIN_CNT) - 1) != 0)
				return -1;
			return chksum;
		case '/':
			*np = '\0';
			return -1;
		default:
			c = win2unixchr(tmpbuf, code, pmp);
			while (*c != '\0')
				*np++ = *c++;
			break;
		}
		cp += 2;
	}
	for (cp = wep->wePart3, i = sizeof(wep->wePart3)/2; --i >= 0;) {
		code = (cp[1] << 8) | cp[0];
		switch (code) {
		case 0:
			*np = '\0';
			if (mbnambuf_write(nbp, name,
			    (wep->weCnt & WIN_CNT) - 1) != 0)
				return -1;
			return chksum;
		case '/':
			*np = '\0';
			return -1;
		default:
			c = win2unixchr(tmpbuf, code, pmp);
			while (*c != '\0')
				*np++ = *c++;
			break;
		}
		cp += 2;
	}
	*np = '\0';
	if (mbnambuf_write(nbp, name, (wep->weCnt & WIN_CNT) - 1) != 0)
		return -1;
	return chksum;
}