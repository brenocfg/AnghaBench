#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* s2; void* s1; } ;
struct rpc_err {int re_status; TYPE_1__ re_lb; } ;
typedef  void* int32_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  enum accept_stat { ____Placeholder_accept_stat } accept_stat ;

/* Variables and functions */
#define  GARBAGE_ARGS 133 
 scalar_t__ MSG_ACCEPTED ; 
#define  PROC_UNAVAIL 132 
#define  PROG_MISMATCH 131 
#define  PROG_UNAVAIL 130 
 int RPC_CANTDECODEARGS ; 
 int RPC_FAILED ; 
 int RPC_PROCUNAVAIL ; 
 int RPC_PROGUNAVAIL ; 
 int RPC_PROGVERSMISMATCH ; 
 int RPC_SUCCESS ; 
 int RPC_SYSTEMERROR ; 
#define  SUCCESS 129 
#define  SYSTEM_ERR 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum clnt_stat
accepted(enum accept_stat acpt_stat, struct rpc_err *error)
{

	assert(error != NULL);

	switch (acpt_stat) {

	case PROG_UNAVAIL:
		error->re_status = RPC_PROGUNAVAIL;
		return (RPC_PROGUNAVAIL);

	case PROG_MISMATCH:
		error->re_status = RPC_PROGVERSMISMATCH;
		return (RPC_PROGVERSMISMATCH);

	case PROC_UNAVAIL:
		return (RPC_PROCUNAVAIL);

	case GARBAGE_ARGS:
		return (RPC_CANTDECODEARGS);

	case SYSTEM_ERR:
		return (RPC_SYSTEMERROR);

	case SUCCESS:
		return (RPC_SUCCESS);
	}
	/* NOTREACHED */
	/* something's wrong, but we don't know what ... */
	error->re_lb.s1 = (int32_t)MSG_ACCEPTED;
	error->re_lb.s2 = (int32_t)acpt_stat;
	return (RPC_FAILED);
}