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
typedef  enum skd_req_state { ____Placeholder_skd_req_state } skd_req_state ;

/* Variables and functions */
#define  SKD_REQ_STATE_BUSY 132 
#define  SKD_REQ_STATE_COMPLETED 131 
#define  SKD_REQ_STATE_IDLE 130 
#define  SKD_REQ_STATE_SETUP 129 
#define  SKD_REQ_STATE_TIMEOUT 128 

__attribute__((used)) static const char *skd_skreq_state_to_str(enum skd_req_state state)
{
	switch (state) {
	case SKD_REQ_STATE_IDLE:
		return "IDLE";
	case SKD_REQ_STATE_SETUP:
		return "SETUP";
	case SKD_REQ_STATE_BUSY:
		return "BUSY";
	case SKD_REQ_STATE_COMPLETED:
		return "COMPLETED";
	case SKD_REQ_STATE_TIMEOUT:
		return "TIMEOUT";
	default:
		return "???";
	}
}