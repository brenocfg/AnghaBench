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
typedef  int EapMethodState ;

/* Variables and functions */
#define  METHOD_CONT 132 
#define  METHOD_DONE 131 
#define  METHOD_INIT 130 
#define  METHOD_MAY_CONT 129 
#define  METHOD_NONE 128 

__attribute__((used)) static const char * eap_sm_method_state_txt(EapMethodState state)
{
	switch (state) {
	case METHOD_NONE:
		return "NONE";
	case METHOD_INIT:
		return "INIT";
	case METHOD_CONT:
		return "CONT";
	case METHOD_MAY_CONT:
		return "MAY_CONT";
	case METHOD_DONE:
		return "DONE";
	default:
		return "UNKNOWN";
	}
}