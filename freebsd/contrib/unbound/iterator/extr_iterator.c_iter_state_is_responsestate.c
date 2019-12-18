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
typedef  enum iter_state { ____Placeholder_iter_state } iter_state ;

/* Variables and functions */
#define  COLLECT_CLASS_STATE 132 
#define  INIT_REQUEST_2_STATE 131 
#define  INIT_REQUEST_3_STATE 130 
#define  INIT_REQUEST_STATE 129 
#define  QUERYTARGETS_STATE 128 

int 
iter_state_is_responsestate(enum iter_state s)
{
	switch(s) {
		case INIT_REQUEST_STATE :
		case INIT_REQUEST_2_STATE :
		case INIT_REQUEST_3_STATE :
		case QUERYTARGETS_STATE :
		case COLLECT_CLASS_STATE :
			return 0;
		default:
			break;
	}
	return 1;
}