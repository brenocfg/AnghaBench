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

__attribute__((used)) static inline signed long ecard_gets24(unsigned char *v)
{
	return v[0] | v[1] << 8 | v[2] << 16 | ((v[2] & 0x80) ? 0xff000000 : 0);
}