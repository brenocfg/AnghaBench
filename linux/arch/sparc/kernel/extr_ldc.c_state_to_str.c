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
typedef  int u8 ;

/* Variables and functions */
#define  LDC_STATE_BOUND 132 
#define  LDC_STATE_CONNECTED 131 
#define  LDC_STATE_INIT 130 
#define  LDC_STATE_INVALID 129 
#define  LDC_STATE_READY 128 

__attribute__((used)) static const char *state_to_str(u8 state)
{
	switch (state) {
	case LDC_STATE_INVALID:
		return "INVALID";
	case LDC_STATE_INIT:
		return "INIT";
	case LDC_STATE_BOUND:
		return "BOUND";
	case LDC_STATE_READY:
		return "READY";
	case LDC_STATE_CONNECTED:
		return "CONNECTED";
	default:
		return "<UNKNOWN>";
	}
}