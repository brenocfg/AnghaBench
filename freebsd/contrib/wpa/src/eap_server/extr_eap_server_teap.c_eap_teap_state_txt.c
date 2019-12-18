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
#define  CRYPTO_BINDING 139 
#define  FAILURE 138 
#define  FAILURE_SEND_RESULT 137 
#define  PHASE1 136 
#define  PHASE1B 135 
#define  PHASE2_BASIC_AUTH 134 
#define  PHASE2_ID 133 
#define  PHASE2_METHOD 132 
#define  PHASE2_START 131 
#define  REQUEST_PAC 130 
#define  START 129 
#define  SUCCESS 128 

__attribute__((used)) static const char * eap_teap_state_txt(int state)
{
	switch (state) {
	case START:
		return "START";
	case PHASE1:
		return "PHASE1";
	case PHASE1B:
		return "PHASE1B";
	case PHASE2_START:
		return "PHASE2_START";
	case PHASE2_ID:
		return "PHASE2_ID";
	case PHASE2_BASIC_AUTH:
		return "PHASE2_BASIC_AUTH";
	case PHASE2_METHOD:
		return "PHASE2_METHOD";
	case CRYPTO_BINDING:
		return "CRYPTO_BINDING";
	case REQUEST_PAC:
		return "REQUEST_PAC";
	case FAILURE_SEND_RESULT:
		return "FAILURE_SEND_RESULT";
	case SUCCESS:
		return "SUCCESS";
	case FAILURE:
		return "FAILURE";
	default:
		return "Unknown?!";
	}
}