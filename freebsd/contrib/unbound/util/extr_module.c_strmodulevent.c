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
typedef  enum module_ev { ____Placeholder_module_ev } module_ev ;

/* Variables and functions */
#define  module_event_capsfail 134 
#define  module_event_error 133 
#define  module_event_moddone 132 
#define  module_event_new 131 
#define  module_event_noreply 130 
#define  module_event_pass 129 
#define  module_event_reply 128 

const char* 
strmodulevent(enum module_ev e)
{
	switch(e) {
	case module_event_new: return "module_event_new";
	case module_event_pass: return "module_event_pass";
	case module_event_reply: return "module_event_reply";
	case module_event_noreply: return "module_event_noreply";
	case module_event_capsfail: return "module_event_capsfail";
	case module_event_moddone: return "module_event_moddone";
	case module_event_error: return "module_event_error";
	}
	return "bad_event_value";
}