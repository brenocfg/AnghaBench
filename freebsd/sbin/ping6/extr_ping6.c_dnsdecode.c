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
typedef  int /*<<< orphan*/  cresult ;

/* Variables and functions */
 int /*<<< orphan*/  MAXDNAME ; 
 scalar_t__ isprint (int const) ; 
 int snprintf (char*,int,char*,int const) ; 
 size_t strlcat (char*,char*,size_t) ; 

__attribute__((used)) static const char *
dnsdecode(const u_char *sp, const u_char *ep, const u_char *base, char *buf,
	size_t bufsiz)
{
	int i;
	const u_char *cp;
	char cresult[MAXDNAME + 1];
	const u_char *comp;
	int l;

	cp = sp;
	*buf = '\0';

	if (cp >= ep)
		return NULL;
	while (cp < ep) {
		i = *cp;
		if (i == 0 || cp != sp) {
			if (strlcat((char *)buf, ".", bufsiz) >= bufsiz)
				return NULL;	/*result overrun*/
		}
		if (i == 0)
			break;
		cp++;

		if ((i & 0xc0) == 0xc0 && cp - base > (i & 0x3f)) {
			/* DNS compression */
			if (!base)
				return NULL;

			comp = base + (i & 0x3f);
			if (dnsdecode(comp, cp, base, cresult,
			    sizeof(cresult)) == NULL)
				return NULL;
			if (strlcat(buf, cresult, bufsiz) >= bufsiz)
				return NULL;	/*result overrun*/
			break;
		} else if ((i & 0x3f) == i) {
			if (i > ep - cp)
				return NULL;	/*source overrun*/
			while (i-- > 0 && cp < ep) {
				l = snprintf(cresult, sizeof(cresult),
				    isprint(*cp) ? "%c" : "\\%03o", *cp & 0xff);
				if ((size_t)l >= sizeof(cresult) || l < 0)
					return NULL;
				if (strlcat(buf, cresult, bufsiz) >= bufsiz)
					return NULL;	/*result overrun*/
				cp++;
			}
		} else
			return NULL;	/*invalid label*/
	}
	if (i != 0)
		return NULL;	/*not terminated*/
	cp++;
	return cp;
}