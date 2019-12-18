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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int IDENT_SEND ; 
#define  IDENT_WAIT 128 
 int be_state ; 
 int /*<<< orphan*/  ident_idx ; 

__attribute__((used)) static void
fwctl_outw(uint16_t val)
{
	switch (be_state) {
	case IDENT_WAIT:
		if (val == 0) {
			be_state = IDENT_SEND;
			ident_idx = 0;
		}
		break;
	default:
		/* ignore */
		break;
	}
}