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

__attribute__((used)) static bool
data_desc(int sd_type)
{
	/* data descriptor or a readable code descriptor */
	return ((sd_type & 0x18) == 0x10 || (sd_type & 0x1A) == 0x1A);
}