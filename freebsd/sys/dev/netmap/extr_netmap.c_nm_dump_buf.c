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
 char P_C (char) ; 
 char P_HI (char) ; 
 char P_LO (char) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 

const char *
nm_dump_buf(char *p, int len, int lim, char *dst)
{
	static char _dst[8192];
	int i, j, i0;
	static char hex[] ="0123456789abcdef";
	char *o;	/* output position */

#define P_HI(x)	hex[((x) & 0xf0)>>4]
#define P_LO(x)	hex[((x) & 0xf)]
#define P_C(x)	((x) >= 0x20 && (x) <= 0x7e ? (x) : '.')
	if (!dst)
		dst = _dst;
	if (lim <= 0 || lim > len)
		lim = len;
	o = dst;
	sprintf(o, "buf 0x%p len %d lim %d\n", p, len, lim);
	o += strlen(o);
	/* hexdump routine */
	for (i = 0; i < lim; ) {
		sprintf(o, "%5d: ", i);
		o += strlen(o);
		memset(o, ' ', 48);
		i0 = i;
		for (j=0; j < 16 && i < lim; i++, j++) {
			o[j*3] = P_HI(p[i]);
			o[j*3+1] = P_LO(p[i]);
		}
		i = i0;
		for (j=0; j < 16 && i < lim; i++, j++)
			o[j + 48] = P_C(p[i]);
		o[j+48] = '\n';
		o += j+49;
	}
	*o = '\0';
#undef P_HI
#undef P_LO
#undef P_C
	return dst;
}