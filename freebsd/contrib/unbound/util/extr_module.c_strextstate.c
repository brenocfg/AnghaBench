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
typedef  enum module_ext_state { ____Placeholder_module_ext_state } module_ext_state ;

/* Variables and functions */
#define  module_error 134 
#define  module_finished 133 
#define  module_restart_next 132 
#define  module_state_initial 131 
#define  module_wait_module 130 
#define  module_wait_reply 129 
#define  module_wait_subquery 128 

const char* 
strextstate(enum module_ext_state s)
{
	switch(s) {
	case module_state_initial: return "module_state_initial";
	case module_wait_reply: return "module_wait_reply";
	case module_wait_module: return "module_wait_module";
	case module_restart_next: return "module_restart_next";
	case module_wait_subquery: return "module_wait_subquery";
	case module_error: return "module_error";
	case module_finished: return "module_finished";
	}
	return "bad_extstate_value";
}