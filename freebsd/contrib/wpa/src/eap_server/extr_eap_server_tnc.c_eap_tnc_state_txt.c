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
typedef  enum eap_tnc_state { ____Placeholder_eap_tnc_state } eap_tnc_state ;

/* Variables and functions */
#define  CONTINUE 134 
#define  DONE 133 
#define  FAIL 132 
#define  FRAG_ACK 131 
#define  RECOMMENDATION 130 
#define  START 129 
#define  WAIT_FRAG_ACK 128 

__attribute__((used)) static const char * eap_tnc_state_txt(enum eap_tnc_state state)
{
	switch (state) {
	case START:
		return "START";
	case CONTINUE:
		return "CONTINUE";
	case RECOMMENDATION:
		return "RECOMMENDATION";
	case FRAG_ACK:
		return "FRAG_ACK";
	case WAIT_FRAG_ACK:
		return "WAIT_FRAG_ACK";
	case DONE:
		return "DONE";
	case FAIL:
		return "FAIL";
	}
	return "??";
}