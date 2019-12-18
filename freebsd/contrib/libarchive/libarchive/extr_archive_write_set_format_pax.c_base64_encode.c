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
typedef  size_t v ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static char *
base64_encode(const char *s, size_t len)
{
	static const char digits[64] =
	    { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
	      'P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d',
	      'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
	      't','u','v','w','x','y','z','0','1','2','3','4','5','6','7',
	      '8','9','+','/' };
	int v;
	char *d, *out;

	/* 3 bytes becomes 4 chars, but round up and allow for trailing NUL */
	out = (char *)malloc((len * 4 + 2) / 3 + 1);
	if (out == NULL)
		return (NULL);
	d = out;

	/* Convert each group of 3 bytes into 4 characters. */
	while (len >= 3) {
		v = (((int)s[0] << 16) & 0xff0000)
		    | (((int)s[1] << 8) & 0xff00)
		    | (((int)s[2]) & 0x00ff);
		s += 3;
		len -= 3;
		*d++ = digits[(v >> 18) & 0x3f];
		*d++ = digits[(v >> 12) & 0x3f];
		*d++ = digits[(v >> 6) & 0x3f];
		*d++ = digits[(v) & 0x3f];
	}
	/* Handle final group of 1 byte (2 chars) or 2 bytes (3 chars). */
	switch (len) {
	case 0: break;
	case 1:
		v = (((int)s[0] << 16) & 0xff0000);
		*d++ = digits[(v >> 18) & 0x3f];
		*d++ = digits[(v >> 12) & 0x3f];
		break;
	case 2:
		v = (((int)s[0] << 16) & 0xff0000)
		    | (((int)s[1] << 8) & 0xff00);
		*d++ = digits[(v >> 18) & 0x3f];
		*d++ = digits[(v >> 12) & 0x3f];
		*d++ = digits[(v >> 6) & 0x3f];
		break;
	}
	/* Add trailing NUL character so output is a valid C string. */
	*d = '\0';
	return (out);
}