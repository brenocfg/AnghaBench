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
#define  UB_AFTERFINAL 138 
#define  UB_FORKFAIL 137 
#define  UB_INITFAIL 136 
#define  UB_NOERROR 135 
#define  UB_NOID 134 
#define  UB_NOMEM 133 
#define  UB_PIPE 132 
#define  UB_READFILE 131 
#define  UB_SERVFAIL 130 
#define  UB_SOCKET 129 
#define  UB_SYNTAX 128 

const char* 
ub_strerror(int err)
{
	switch(err) {
		case UB_NOERROR: return "no error";
		case UB_SOCKET: return "socket io error";
		case UB_NOMEM: return "out of memory";
		case UB_SYNTAX: return "syntax error";
		case UB_SERVFAIL: return "server failure";
		case UB_FORKFAIL: return "could not fork";
		case UB_INITFAIL: return "initialization failure";
		case UB_AFTERFINAL: return "setting change after finalize";
		case UB_PIPE: return "error in pipe communication with async";
		case UB_READFILE: return "error reading file";
		case UB_NOID: return "error async_id does not exist";
		default: return "unknown error";
	}
}