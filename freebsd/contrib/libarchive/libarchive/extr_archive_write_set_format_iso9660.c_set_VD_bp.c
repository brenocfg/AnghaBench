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
typedef  enum VD_type { ____Placeholder_VD_type } VD_type ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 

__attribute__((used)) static void
set_VD_bp(unsigned char *bp, enum VD_type type, unsigned char ver)
{

	/* Volume Descriptor Type */
	bp[1] = (unsigned char)type;
	/* Standard Identifier */
	memcpy(bp + 2, "CD001", 5);
	/* Volume Descriptor Version */
	bp[7] = ver;
}