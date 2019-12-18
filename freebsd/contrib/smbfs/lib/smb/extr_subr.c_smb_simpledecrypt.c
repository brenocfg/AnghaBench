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
 int EINVAL ; 
 scalar_t__ isascii (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strtoul (char*,char**,int) ; 

int
smb_simpledecrypt(char *dst, const char *src)
{
	char *ep, hexval[3];
	int len, ch, pos;

	if (strncmp(src, "$$1", 3) != 0)
		return EINVAL;
	src += 3;
	len = strlen(src);
	if (len & 1)
		return EINVAL;
	len /= 2;
	hexval[2] = 0;
	pos = 27;
	while (len--) {
		hexval[0] = *src++;
		hexval[1] = *src++;
		ch = strtoul(hexval, &ep, 16);
		if (*ep != 0)
			return EINVAL;
		ch ^= pos;
		pos += 13;
		if (pos > 256)
			pos -= 256;
		if (isascii(ch))
		    ch = (isupper(ch) ? ('A' + (ch - 'A' + 13) % 26) :
			  islower(ch) ? ('a' + (ch - 'a' + 13) % 26) : ch);
		*dst++ = ch;
	}
	*dst = 0;
	return 0;
}