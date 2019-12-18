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
#define  COLLECT_CLASS_STATE 136 
#define  DSNS_FIND_STATE 135 
#define  FINISHED_STATE 134 
#define  INIT_REQUEST_2_STATE 133 
#define  INIT_REQUEST_3_STATE 132 
#define  INIT_REQUEST_STATE 131 
#define  PRIME_RESP_STATE 130 
#define  QUERYTARGETS_STATE 129 
#define  QUERY_RESP_STATE 128 

const char* 
iter_state_to_string(enum iter_state state)
{
	switch (state)
	{
	case INIT_REQUEST_STATE :
		return "INIT REQUEST STATE";
	case INIT_REQUEST_2_STATE :
		return "INIT REQUEST STATE (stage 2)";
	case INIT_REQUEST_3_STATE:
		return "INIT REQUEST STATE (stage 3)";
	case QUERYTARGETS_STATE :
		return "QUERY TARGETS STATE";
	case PRIME_RESP_STATE :
		return "PRIME RESPONSE STATE";
	case COLLECT_CLASS_STATE :
		return "COLLECT CLASS STATE";
	case DSNS_FIND_STATE :
		return "DSNS FIND STATE";
	case QUERY_RESP_STATE :
		return "QUERY RESPONSE STATE";
	case FINISHED_STATE :
		return "FINISHED RESPONSE STATE";
	default :
		return "UNKNOWN ITER STATE";
	}
}