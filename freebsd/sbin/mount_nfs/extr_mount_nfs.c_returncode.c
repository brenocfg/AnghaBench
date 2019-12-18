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
struct rpc_err {int /*<<< orphan*/  re_errno; } ;
typedef  enum tryret { ____Placeholder_tryret } tryret ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
#define  ENOMEM 136 
#define  ETIMEDOUT 135 
#define  RPC_CANTRECV 134 
#define  RPC_CANTSEND 133 
#define  RPC_PMAPFAILURE 132 
#define  RPC_PROGNOTREGISTERED 131 
#define  RPC_PROGVERSMISMATCH 130 
#define  RPC_SYSTEMERROR 129 
#define  RPC_TIMEDOUT 128 
 int TRYRET_LOCALERR ; 
 int TRYRET_REMOTEERR ; 
 int TRYRET_TIMEOUT ; 

__attribute__((used)) static enum tryret
returncode(enum clnt_stat clntstat, struct rpc_err *rpcerr)
{

	switch (clntstat) {
	case RPC_TIMEDOUT:
		return (TRYRET_TIMEOUT);
	case RPC_PMAPFAILURE:
	case RPC_PROGNOTREGISTERED:
	case RPC_PROGVERSMISMATCH:
	/* XXX, these can be local or remote. */
	case RPC_CANTSEND:
	case RPC_CANTRECV:
		return (TRYRET_REMOTEERR);
	case RPC_SYSTEMERROR:
		switch (rpcerr->re_errno) {
		case ETIMEDOUT:
			return (TRYRET_TIMEOUT);
		case ENOMEM:
			break;
		default:
			return (TRYRET_REMOTEERR);
		}
		/* FALLTHROUGH */
	default:
		break;
	}
	return (TRYRET_LOCALERR);
}