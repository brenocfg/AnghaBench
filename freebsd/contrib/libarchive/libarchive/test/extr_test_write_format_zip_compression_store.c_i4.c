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
 int i2 (unsigned char const*) ; 

__attribute__((used)) static unsigned int
i4(const void *p_)
{
	const unsigned char *p = p_;
	return (i2(p) | (i2(p + 2) << 16));
}