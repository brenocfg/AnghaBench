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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be16 (int,int*) ; 

__attribute__((used)) static inline uint8_t *encode_tag_length(uint8_t *buf, uint8_t tag,
					 uint32_t len)
{
	*buf++ = tag;

	if (len <= 127) {
		buf[0] = len;
		return buf + 1;
	}

	if (len <= 255) {
		buf[0] = 0x81;
		buf[1] = len;
		return buf + 2;
	}

	buf[0] = 0x82;
	put_unaligned_be16(len, buf + 1);
	return buf + 3;
}