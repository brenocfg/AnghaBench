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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static size_t _unmarshall64(uint8_t * inbuf, uint64_t * num)
{
	(*num) = (uint64_t) inbuf[0];
	(*num) |= ((uint64_t) inbuf[1] << 8);
	(*num) |= ((uint64_t) inbuf[2] << 16);
	(*num) |= ((uint64_t) inbuf[3] << 24);
	(*num) |= ((uint64_t) inbuf[4] << 32);
	(*num) |= ((uint64_t) inbuf[5] << 40);
	(*num) |= ((uint64_t) inbuf[6] << 48);
	(*num) |= ((uint64_t) inbuf[7] << 56);

	return (sizeof(*num));
}