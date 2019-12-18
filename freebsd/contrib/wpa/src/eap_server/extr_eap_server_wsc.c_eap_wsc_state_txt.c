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
#define  DONE 133 
#define  FAIL 132 
#define  FRAG_ACK 131 
#define  MESG 130 
#define  START 129 
#define  WAIT_FRAG_ACK 128 

__attribute__((used)) static const char * eap_wsc_state_txt(int state)
{
	switch (state) {
	case START:
		return "START";
	case MESG:
		return "MESG";
	case FRAG_ACK:
		return "FRAG_ACK";
	case WAIT_FRAG_ACK:
		return "WAIT_FRAG_ACK";
	case DONE:
		return "DONE";
	case FAIL:
		return "FAIL";
	default:
		return "?";
	}
}