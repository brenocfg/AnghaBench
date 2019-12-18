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
typedef  int /*<<< orphan*/  num ;

/* Variables and functions */

__attribute__((used)) static size_t _marshall64(uint8_t * outbuf, uint64_t num)
{
	outbuf[0] = (uint8_t) num;
	outbuf[1] = (uint8_t) (num >> 8);
	outbuf[2] = (uint8_t) (num >> 16);
	outbuf[3] = (uint8_t) (num >> 24);
	outbuf[4] = (uint8_t) (num >> 32);
	outbuf[5] = (uint8_t) (num >> 40);
	outbuf[6] = (uint8_t) (num >> 48);
	outbuf[7] = (uint8_t) (num >> 56);

	return (sizeof(num));
}