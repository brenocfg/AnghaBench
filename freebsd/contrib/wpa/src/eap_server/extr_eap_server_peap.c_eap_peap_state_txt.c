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
#define  FAILURE 139 
#define  FAILURE_REQ 138 
#define  PHASE1 137 
#define  PHASE1_ID2 136 
#define  PHASE2_ID 135 
#define  PHASE2_METHOD 134 
#define  PHASE2_SOH 133 
#define  PHASE2_START 132 
#define  PHASE2_TLV 131 
#define  START 130 
#define  SUCCESS 129 
#define  SUCCESS_REQ 128 

__attribute__((used)) static const char * eap_peap_state_txt(int state)
{
	switch (state) {
	case START:
		return "START";
	case PHASE1:
		return "PHASE1";
	case PHASE1_ID2:
		return "PHASE1_ID2";
	case PHASE2_START:
		return "PHASE2_START";
	case PHASE2_ID:
		return "PHASE2_ID";
	case PHASE2_METHOD:
		return "PHASE2_METHOD";
	case PHASE2_SOH:
		return "PHASE2_SOH";
	case PHASE2_TLV:
		return "PHASE2_TLV";
	case SUCCESS_REQ:
		return "SUCCESS_REQ";
	case FAILURE_REQ:
		return "FAILURE_REQ";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	default:
		return "Unknown?!";
	}
}