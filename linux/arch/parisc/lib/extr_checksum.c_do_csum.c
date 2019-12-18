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
 int /*<<< orphan*/  addc (unsigned int,unsigned int) ; 
 unsigned int be16_to_cpu (unsigned char const) ; 
 unsigned int from32to16 (unsigned int) ; 
 scalar_t__ le16_to_cpu (unsigned char const) ; 
 unsigned int swab16 (unsigned int) ; 

__attribute__((used)) static inline unsigned int do_csum(const unsigned char * buff, int len)
{
	int odd, count;
	unsigned int result = 0;

	if (len <= 0)
		goto out;
	odd = 1 & (unsigned long) buff;
	if (odd) {
		result = be16_to_cpu(*buff);
		len--;
		buff++;
	}
	count = len >> 1;		/* nr of 16-bit words.. */
	if (count) {
		if (2 & (unsigned long) buff) {
			result += *(unsigned short *) buff;
			count--;
			len -= 2;
			buff += 2;
		}
		count >>= 1;		/* nr of 32-bit words.. */
		if (count) {
			while (count >= 4) {
				unsigned int r1, r2, r3, r4;
				r1 = *(unsigned int *)(buff + 0);
				r2 = *(unsigned int *)(buff + 4);
				r3 = *(unsigned int *)(buff + 8);
				r4 = *(unsigned int *)(buff + 12);
				addc(result, r1);
				addc(result, r2);
				addc(result, r3);
				addc(result, r4);
				count -= 4;
				buff += 16;
			}
			while (count) {
				unsigned int w = *(unsigned int *) buff;
				count--;
				buff += 4;
				addc(result, w);
			}
			result = (result & 0xffff) + (result >> 16);
		}
		if (len & 2) {
			result += *(unsigned short *) buff;
			buff += 2;
		}
	}
	if (len & 1)
		result += le16_to_cpu(*buff);
	result = from32to16(result);
	if (odd)
		result = swab16(result);
out:
	return result;
}