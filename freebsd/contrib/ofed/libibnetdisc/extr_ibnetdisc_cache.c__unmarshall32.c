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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static size_t _unmarshall32(uint8_t * inbuf, uint32_t * num)
{
	(*num) = (uint32_t) inbuf[0];
	(*num) |= ((uint32_t) inbuf[1] << 8);
	(*num) |= ((uint32_t) inbuf[2] << 16);
	(*num) |= ((uint32_t) inbuf[3] << 24);

	return (sizeof(*num));
}