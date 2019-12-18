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
 scalar_t__ strchr (char const*,unsigned char) ; 

__attribute__((used)) static int mode2level(const char *__restrict mode)
{
	int i, compress_level = -1;
	for (i = 0; mode[i]; ++i)
		if (mode[i] >= '0' && mode[i] <= '9') break;
	if (mode[i]) compress_level = (int)mode[i] - '0';
	if (strchr(mode, 'u')) compress_level = 0;
	return compress_level;
}