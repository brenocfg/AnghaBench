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

__attribute__((used)) static uint32_t get_be32(void *data)
{
	unsigned char *p = data;

	return (((uint32_t)p[0]) << 24) |
	       (((uint32_t)p[1]) << 16) |
	       (((uint32_t)p[2]) << 8) |
	       ((uint32_t)p[3]);
}