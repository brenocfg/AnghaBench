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

__attribute__((used)) static void validate_width(int width, int peerwidth, int lwa)
{
	if ((width & peerwidth & 0x8)) {
		if (lwa != 8)
			IBWARN
			    ("Peer ports operating at active width %d rather than 8 (12x)",
			     lwa);
	} else if ((width & peerwidth & 0x4)) {
		if (lwa != 4)
			IBWARN
			    ("Peer ports operating at active width %d rather than 4 (8x)",
			     lwa);
	} else if ((width & peerwidth & 0x2)) {
		if (lwa != 2)
			IBWARN
			    ("Peer ports operating at active width %d rather than 2 (4x)",
			     lwa);
	} else if ((width & peerwidth & 0x10)) {
		if (lwa != 16)
			IBWARN
			    ("Peer ports operating at active width %d rather than 16 (2x)",
			      lwa);
	} else if ((width & peerwidth & 0x1)) {
		if (lwa != 1)
			IBWARN
			    ("Peer ports operating at active width %d rather than 1 (1x)",
			     lwa);
	}
}