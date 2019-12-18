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
struct ptrace_lwpinfo {int pl_event; } ;

/* Variables and functions */
#define  PL_EVENT_NONE 129 
#define  PL_EVENT_SIGNAL 128 

__attribute__((used)) static const char *
decode_pl_event(struct ptrace_lwpinfo *lwpinfo)
{

	switch (lwpinfo->pl_event) {
	case PL_EVENT_NONE:
		return ("NONE");

	case PL_EVENT_SIGNAL:
		return ("SIG");

	default:
		return ("UNKNOWN");
	}
}