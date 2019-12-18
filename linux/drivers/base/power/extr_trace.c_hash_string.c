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

__attribute__((used)) static unsigned int hash_string(unsigned int seed, const char *data, unsigned int mod)
{
	unsigned char c;
	while ((c = *data++) != 0) {
		seed = (seed << 16) + (seed << 6) - seed + c;
	}
	return seed % mod;
}