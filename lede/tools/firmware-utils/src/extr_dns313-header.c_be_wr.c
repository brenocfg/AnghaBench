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

__attribute__((used)) static void be_wr(unsigned char *buf, uint32_t val)
{
	buf[0] = (val >> 24) & 0xFFU;
	buf[1] = (val >> 16) & 0xFFU;
	buf[2] = (val >> 8) & 0xFFU;
	buf[3] = val & 0xFFU;
}