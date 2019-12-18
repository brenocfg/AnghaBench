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
typedef  unsigned long u_char ;

/* Variables and functions */

__attribute__((used)) static void
lba2msf(unsigned long lba, u_char *m, u_char *s, u_char *f)
{
	lba += 150;			/* block start offset */
	lba &= 0xffffff;		/* negative lbas use only 24 bits */
	*m = lba / (60 * 75);
	lba %= (60 * 75);
	*s = lba / 75;
	*f = lba % 75;
}