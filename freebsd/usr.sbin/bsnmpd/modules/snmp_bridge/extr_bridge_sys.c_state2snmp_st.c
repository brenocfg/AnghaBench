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
typedef  int uint8_t ;

/* Variables and functions */
#define  BSTP_IFSTATE_BLOCKING 133 
#define  BSTP_IFSTATE_DISABLED 132 
#define  BSTP_IFSTATE_DISCARDING 131 
#define  BSTP_IFSTATE_FORWARDING 130 
#define  BSTP_IFSTATE_LEARNING 129 
#define  BSTP_IFSTATE_LISTENING 128 
 int StpPortState_blocking ; 
 int StpPortState_broken ; 
 int StpPortState_disabled ; 
 int StpPortState_forwarding ; 
 int StpPortState_learning ; 
 int StpPortState_listening ; 

__attribute__((used)) static int
state2snmp_st(uint8_t ifbr_state)
{
	switch (ifbr_state) {
		case BSTP_IFSTATE_DISABLED:
			return (StpPortState_disabled);
		case BSTP_IFSTATE_LISTENING:
			return (StpPortState_listening);
		case BSTP_IFSTATE_LEARNING:
			return (StpPortState_learning);
		case BSTP_IFSTATE_FORWARDING:
			return (StpPortState_forwarding);
		case BSTP_IFSTATE_BLOCKING:
		case BSTP_IFSTATE_DISCARDING:
			return (StpPortState_blocking);
	}

	return (StpPortState_broken);
}