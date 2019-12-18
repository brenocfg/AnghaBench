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

/* Variables and functions */

__attribute__((used)) static __inline__ unsigned long get_be32(void *buf)
{
	unsigned char *p = buf;

	return (((unsigned long) p[0] << 24) +
	        ((unsigned long) p[1] << 16) +
	        ((unsigned long) p[2] << 8) +
	        (unsigned long) p[3]);
}