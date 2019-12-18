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
#define  SCTP_ACTIVE 130 
#define  SCTP_INACTIVE 129 
#define  SCTP_UNCONFIRMED 128 

__attribute__((used)) static const char *
sctp_path_state(int state)
{
	switch (state) {
	case SCTP_UNCONFIRMED:
		return "UNCONFIRMED";
		break;
	case SCTP_ACTIVE:
		return "ACTIVE";
		break;
	case SCTP_INACTIVE:
		return "INACTIVE";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}