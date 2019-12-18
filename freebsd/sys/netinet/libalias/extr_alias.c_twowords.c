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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static __inline int
twowords(void *p)
{
	uint8_t *c = p;

#if BYTE_ORDER == LITTLE_ENDIAN
	uint16_t s1 = ((uint16_t)c[1] << 8) + (uint16_t)c[0];
	uint16_t s2 = ((uint16_t)c[3] << 8) + (uint16_t)c[2];
#else
	uint16_t s1 = ((uint16_t)c[0] << 8) + (uint16_t)c[1];
	uint16_t s2 = ((uint16_t)c[2] << 8) + (uint16_t)c[3];
#endif
	return (s1 + s2);
}