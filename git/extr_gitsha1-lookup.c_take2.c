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
typedef  unsigned char const uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t take2(const unsigned char *sha1)
{
	return ((sha1[0] << 8) | sha1[1]);
}