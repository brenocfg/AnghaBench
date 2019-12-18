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
struct rpc_err {TYPE_1__ re_lb; int /*<<< orphan*/  re_status; } ;
typedef  void* int32_t ;
typedef  enum accept_stat { ____Placeholder_accept_stat } accept_stat ;

/* Variables and functions */
#define  GARBAGE_ARGS 133 
 scalar_t__ MSG_ACCEPTED ; 
#define  PROC_UNAVAIL 132 
#define  PROG_MISMATCH 131 
#define  PROG_UNAVAIL 130 
 int /*<<< orphan*/  RPC_CANTDECODEARGS ; 
 int /*<<< orphan*/  RPC_FAILED ; 
 int /*<<< orphan*/  RPC_PROCUNAVAIL ; 
 int /*<<< orphan*/  RPC_PROGUNAVAIL ; 
 int /*<<< orphan*/  RPC_PROGVERSMISMATCH ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 int /*<<< orphan*/  RPC_SYSTEMERROR ; 
#define  SUCCESS 129 
#define  SYSTEM_ERR 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
accepted(enum accept_stat acpt_stat, struct rpc_err *error)
{

	assert(error != NULL);

	switch (acpt_stat) {

	case PROG_UNAVAIL:
		error->re_status = RPC_PROGUNAVAIL;
		return;

	case PROG_MISMATCH:
		error->re_status = RPC_PROGVERSMISMATCH;
		return;

	case PROC_UNAVAIL:
		error->re_status = RPC_PROCUNAVAIL;
		return;

	case GARBAGE_ARGS:
		error->re_status = RPC_CANTDECODEARGS;
		return;

	case SYSTEM_ERR:
		error->re_status = RPC_SYSTEMERROR;
		return;

	case SUCCESS:
		error->re_status = RPC_SUCCESS;
		return;
	}
	/* NOTREACHED */
	/* something's wrong, but we don't know what ... */
	error->re_status = RPC_FAILED;
	error->re_lb.s1 = (int32_t)MSG_ACCEPTED;
	error->re_lb.s2 = (int32_t)acpt_stat;
}