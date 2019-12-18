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
 unsigned long ADLER32_BASE ; 

__attribute__((used)) static inline unsigned long update_adler32(unsigned long checksum,
					   const void *buf, int len)
{
	const unsigned char *ptr = (const unsigned char *)buf;
	unsigned long s1 = checksum & 0xffff;
	unsigned long s2 = (checksum >> 16) & 0xffff;

	while (len > 0) {
		unsigned k = len < 5552 ? len : 5552;
		len -= k;

		while (k >= 8) {
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			s1 += *ptr++; s2 += s1;
			k -= 8;
		}

		while (k-- > 0) {
			s1 += *ptr++; s2 += s1;
		}
		s1 = s1 % ADLER32_BASE;
		s2 = s2 % ADLER32_BASE;
	}
	return (s2 << 16) + s1;
}