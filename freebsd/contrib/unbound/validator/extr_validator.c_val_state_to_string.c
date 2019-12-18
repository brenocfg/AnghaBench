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
typedef  enum val_state { ____Placeholder_val_state } val_state ;

/* Variables and functions */
#define  VAL_DLVLOOKUP_STATE 132 
#define  VAL_FINDKEY_STATE 131 
#define  VAL_FINISHED_STATE 130 
#define  VAL_INIT_STATE 129 
#define  VAL_VALIDATE_STATE 128 

const char* 
val_state_to_string(enum val_state state)
{
	switch(state) {
		case VAL_INIT_STATE: return "VAL_INIT_STATE";
		case VAL_FINDKEY_STATE: return "VAL_FINDKEY_STATE";
		case VAL_VALIDATE_STATE: return "VAL_VALIDATE_STATE";
		case VAL_FINISHED_STATE: return "VAL_FINISHED_STATE";
		case VAL_DLVLOOKUP_STATE: return "VAL_DLVLOOKUP_STATE";
	}
	return "UNKNOWN VALIDATOR STATE";
}