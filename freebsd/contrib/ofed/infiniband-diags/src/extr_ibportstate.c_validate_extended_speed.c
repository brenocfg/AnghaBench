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
 int /*<<< orphan*/  IBWARN (char*,int) ; 

__attribute__((used)) static void validate_extended_speed(int espeed, int peerespeed, int lsea)
{
	if ((espeed & peerespeed & 0x2)) {
		if (lsea != 2)
			IBWARN
			    ("Peer ports operating at active extended speed %d rather than 2 (25.78125 Gbps)",
			     lsea);
	} else if ((espeed & peerespeed & 0x1)) {
		if (lsea != 1)
			IBWARN
			    ("Peer ports operating at active extended speed %d rather than 1 (14.0625 Gbps)",
			     lsea);
	}
}