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
 int EOF ; 
 int gdb_rx_char () ; 

int
gdb_rx_bindata(unsigned char *data, size_t datalen, size_t *amt)
{
	int c;

	*amt = 0;

	while (*amt < datalen) {
		c = gdb_rx_char();
		if (c == EOF)
			break;
		/* Escaped character up next */
		if (c == '}') {
			/* Malformed packet. */
			if ((c = gdb_rx_char()) == EOF)
				return (1);
			c ^= 0x20;
		}
		*(data++) = c & 0xff;
		(*amt)++;
	}

	return (0);
}