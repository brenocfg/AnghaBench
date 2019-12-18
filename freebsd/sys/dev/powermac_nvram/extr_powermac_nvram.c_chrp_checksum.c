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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */

__attribute__((used)) static int
chrp_checksum(int sum, uint8_t *data, uint8_t *end)
{

	for (; data < end; data++)
		sum += data[0];
	while (sum > 0xff)
		sum = (sum & 0xff) + (sum >> 8);
	return sum;
}