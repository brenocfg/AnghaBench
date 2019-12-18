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

/* Variables and functions */

__attribute__((used)) static int
fill_checksum(uint8_t *data_out, int len)
{
	int res;
	int i;

	res = 0;
	for (i = 0; i < len; i++) {
		res += data_out[i];
	}

	data_out[len] = (res & 0xff);

	return (0);
}