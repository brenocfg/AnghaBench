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
#define  FAILURE 134 
#define  PHASE1 133 
#define  PHASE2_METHOD 132 
#define  PHASE2_MSCHAPV2_RESP 131 
#define  PHASE2_START 130 
#define  START 129 
#define  SUCCESS 128 

__attribute__((used)) static const char * eap_ttls_state_txt(int state)
{
	switch (state) {
	case START:
		return "START";
	case PHASE1:
		return "PHASE1";
	case PHASE2_START:
		return "PHASE2_START";
	case PHASE2_METHOD:
		return "PHASE2_METHOD";
	case PHASE2_MSCHAPV2_RESP:
		return "PHASE2_MSCHAPV2_RESP";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	default:
		return "Unknown?!";
	}
}