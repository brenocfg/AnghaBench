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
typedef  int uint32_t ;

/* Variables and functions */

int
ar71xx_mac_addr_init(unsigned char *dst, const unsigned char *src,
    int offset, int is_local)
{
	int t;

	if (dst == NULL || src == NULL)
		return (-1);

	/* XXX TODO: validate 'src' is a valid MAC address */

	t = (((uint32_t) src[3]) << 16)
	    + (((uint32_t) src[4]) << 8)
	    + ((uint32_t) src[5]);

	/* Note: this is handles both positive and negative offsets */
	t += offset;

	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = (t >> 16) & 0xff;
	dst[4] = (t >> 8) & 0xff;
	dst[5] = t & 0xff;

	if (is_local)
		dst[0] |= 0x02;

	/* Everything's okay */
	return (0);
}