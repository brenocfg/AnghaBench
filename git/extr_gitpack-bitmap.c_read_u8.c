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
typedef  unsigned char const uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t read_u8(const unsigned char *buffer, size_t *pos)
{
	return buffer[(*pos)++];
}