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
 int /*<<< orphan*/  isNull (struct iso9660*,unsigned char const*,int,int) ; 

__attribute__((used)) static int
isVDSetTerminator(struct iso9660 *iso9660, const unsigned char *h)
{
	(void)iso9660; /* UNUSED */

	/* Type of the Volume Descriptor Set Terminator must be 255. */
	if (h[0] != 255)
		return (0);

	/* Volume Descriptor Version must be 1. */
	if (h[6] != 1)
		return (0);

	/* Reserved field must be 0. */
	if (!isNull(iso9660, h, 7, 2048-7))
		return (0);

	return (1);
}