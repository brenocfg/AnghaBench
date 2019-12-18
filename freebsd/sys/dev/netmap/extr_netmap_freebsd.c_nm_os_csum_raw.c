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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int rawsum_t ;

/* Variables and functions */
 scalar_t__ be16toh (int /*<<< orphan*/ ) ; 

rawsum_t
nm_os_csum_raw(uint8_t *data, size_t len, rawsum_t cur_sum)
{
	/* TODO XXX please use the FreeBSD implementation for this. */
	uint16_t *words = (uint16_t *)data;
	int nw = len / 2;
	int i;

	for (i = 0; i < nw; i++)
		cur_sum += be16toh(words[i]);

	if (len & 1)
		cur_sum += (data[len-1] << 8);

	return cur_sum;
}