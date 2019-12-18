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
typedef  int EapDecision ;

/* Variables and functions */
#define  DECISION_COND_SUCC 130 
#define  DECISION_FAIL 129 
#define  DECISION_UNCOND_SUCC 128 

__attribute__((used)) static const char * eap_sm_decision_txt(EapDecision decision)
{
	switch (decision) {
	case DECISION_FAIL:
		return "FAIL";
	case DECISION_COND_SUCC:
		return "COND_SUCC";
	case DECISION_UNCOND_SUCC:
		return "UNCOND_SUCC";
	default:
		return "UNKNOWN";
	}
}