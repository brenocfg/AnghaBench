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
struct isoent {int ext_off; int ext_len; scalar_t__ identifier; } ;

/* Variables and functions */
 int memcmp (unsigned char const*,unsigned char const*,int) ; 

__attribute__((used)) static int
isoent_cmp_joliet_identifier(const struct isoent *p1, const struct isoent *p2)
{
	const unsigned char *s1, *s2;
	int cmp;
	int l;

	s1 = (const unsigned char *)p1->identifier;
	s2 = (const unsigned char *)p2->identifier;

	/* Compare File Name */
	l = p1->ext_off;
	if (l > p2->ext_off)
		l = p2->ext_off;
	cmp = memcmp(s1, s2, l);
	if (cmp != 0)
		return (cmp);
	if (p1->ext_off < p2->ext_off) {
		s2 += l;
		l = p2->ext_off - p1->ext_off;
		while (l--)
			if (0 != *s2++)
				return (- *(const unsigned char *)(s2 - 1));
	} else if (p1->ext_off > p2->ext_off) {
		s1 += l;
		l = p1->ext_off - p2->ext_off;
		while (l--)
			if (0 != *s1++)
				return (*(const unsigned char *)(s1 - 1));
	}
	/* Compare File Name Extension */
	if (p1->ext_len == 0 && p2->ext_len == 0)
		return (0);
	if (p1->ext_len == 2 && p2->ext_len == 2)
		return (0);
	if (p1->ext_len <= 2)
		return (-1);
	if (p2->ext_len <= 2)
		return (1);
	l = p1->ext_len;
	if (l > p2->ext_len)
		l = p2->ext_len;
	s1 = (unsigned char *)(p1->identifier + p1->ext_off);
	s2 = (unsigned char *)(p2->identifier + p2->ext_off);
	if (l > 1) {
		cmp = memcmp(s1, s2, l);
		if (cmp != 0)
			return (cmp);
	}
	if (p1->ext_len < p2->ext_len) {
		s2 += l;
		l = p2->ext_len - p1->ext_len;
		while (l--)
			if (0 != *s2++)
				return (- *(const unsigned char *)(s2 - 1));
	} else if (p1->ext_len > p2->ext_len) {
		s1 += l;
		l = p1->ext_len - p2->ext_len;
		while (l--)
			if (0 != *s1++)
				return (*(const unsigned char *)(s1 - 1));
	}
	/* Compare File Version Number */
	/* No operation. The File Version Number is always one. */

	return (cmp);
}