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
typedef  int u8_t ;
typedef  int u16_t ;

/* Variables and functions */

__attribute__((used)) static u16_t
chksum(u16_t sum, const u8_t *data, u16_t len)
{
	u16_t t;
	const u8_t *dataptr;
	const u8_t *last_byte;

	dataptr = data;
	last_byte = data + len - 1;

	while(dataptr < last_byte) {	/* At least two more bytes */
		t = (dataptr[0] << 8) + dataptr[1];
		sum += t;
		if(sum < t) {
			sum++;		/* carry */
		}
		dataptr += 2;
	}

	if(dataptr == last_byte) {
		t = (dataptr[0] << 8) + 0;
		sum += t;
		if(sum < t) {
			sum++;		/* carry */
		}
	}

	/* Return sum in host byte order. */
	return sum;
}