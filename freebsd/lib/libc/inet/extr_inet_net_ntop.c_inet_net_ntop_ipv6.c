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
typedef  unsigned char u_int ;
typedef  int u_char ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  SPRINTF (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
inet_net_ntop_ipv6(const u_char *src, int bits, char *dst, size_t size) {
	u_int	m;
	int	b;
	int	p;
	int	zero_s, zero_l, tmp_zero_s, tmp_zero_l;
	int	i;
	int	is_ipv4 = 0;
	unsigned char inbuf[16];
	char outbuf[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255/128")];
	char	*cp;
	int	words;
	u_char	*s;

	if (bits < 0 || bits > 128) {
		errno = EINVAL;
		return (NULL);
	}

	cp = outbuf;

	if (bits == 0) {
		*cp++ = ':';
		*cp++ = ':';
		*cp = '\0';
	} else {
		/* Copy src to private buffer.  Zero host part. */
		p = (bits + 7) / 8;
		memcpy(inbuf, src, p);
		memset(inbuf + p, 0, 16 - p);
		b = bits % 8;
		if (b != 0) {
			m = ~0 << (8 - b);
			inbuf[p-1] &= m;
		}

		s = inbuf;

		/* how many words need to be displayed in output */
		words = (bits + 15) / 16;
		if (words == 1)
			words = 2;

		/* Find the longest substring of zero's */
		zero_s = zero_l = tmp_zero_s = tmp_zero_l = 0;
		for (i = 0; i < (words * 2); i += 2) {
			if ((s[i] | s[i+1]) == 0) {
				if (tmp_zero_l == 0)
					tmp_zero_s = i / 2;
				tmp_zero_l++;
			} else {
				if (tmp_zero_l && zero_l < tmp_zero_l) {
					zero_s = tmp_zero_s;
					zero_l = tmp_zero_l;
					tmp_zero_l = 0;
				}
			}
		}

		if (tmp_zero_l && zero_l < tmp_zero_l) {
			zero_s = tmp_zero_s;
			zero_l = tmp_zero_l;
		}

		if (zero_l != words && zero_s == 0 && ((zero_l == 6) ||
		    ((zero_l == 5 && s[10] == 0xff && s[11] == 0xff) ||
		    ((zero_l == 7 && s[14] != 0 && s[15] != 1)))))
			is_ipv4 = 1;

		/* Format whole words. */
		for (p = 0; p < words; p++) {
			if (zero_l != 0 && p >= zero_s && p < zero_s + zero_l) {
				/* Time to skip some zeros */
				if (p == zero_s)
					*cp++ = ':';
				if (p == words - 1)
					*cp++ = ':';
				s++;
				s++;
				continue;
			}

			if (is_ipv4 && p > 5 ) {
				*cp++ = (p == 6) ? ':' : '.';
				cp += SPRINTF((cp, "%u", *s++));
				/* we can potentially drop the last octet */
				if (p != 7 || bits > 120) {
					*cp++ = '.';
					cp += SPRINTF((cp, "%u", *s++));
				}
			} else {
				if (cp != outbuf)
					*cp++ = ':';
				cp += SPRINTF((cp, "%x", *s * 256 + s[1]));
				s += 2;
			}
		}
	}
	/* Format CIDR /width. */
	sprintf(cp, "/%u", bits);
	if (strlen(outbuf) + 1 > size)
		goto emsgsize;
	strcpy(dst, outbuf);

	return (dst);

emsgsize:
	errno = EMSGSIZE;
	return (NULL);
}