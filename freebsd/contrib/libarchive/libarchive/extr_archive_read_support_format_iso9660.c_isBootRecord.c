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
struct iso9660 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
isBootRecord(struct iso9660 *iso9660, const unsigned char *h)
{
	(void)iso9660; /* UNUSED */

	/* Type of the Volume Descriptor Boot Record must be 0. */
	if (h[0] != 0)
		return (0);

	/* Volume Descriptor Version must be 1. */
	if (h[6] != 1)
		return (0);

	return (1);
}