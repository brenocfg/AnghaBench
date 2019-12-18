#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct rpc_callextra {int dummy; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  int /*<<< orphan*/  res1 ;
typedef  int /*<<< orphan*/  nlm_res ;
struct TYPE_6__ {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  block; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_1__ nlm_cancargs ;
typedef  int /*<<< orphan*/  nlm4_res ;
struct TYPE_7__ {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  block; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_2__ nlm4_cancargs ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ NLM_VERS4 ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int nlm4_cancel_4 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_callextra*,struct timeval) ; 
 int nlm_cancel_1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct rpc_callextra*,struct timeval) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_res (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum clnt_stat
nlm_cancel_rpc(rpcvers_t vers, nlm4_cancargs *args, nlm4_res *res, CLIENT *client,
    struct rpc_callextra *ext, struct timeval timo)
{
	if (vers == NLM_VERS4) {
		return nlm4_cancel_4(args, res, client, ext, timo);
	} else {
		nlm_cancargs args1;
		nlm_res res1;
		enum clnt_stat stat;

		args1.cookie = args->cookie;
		args1.block = args->block;
		args1.exclusive = args->exclusive;
		nlm_convert_to_nlm_lock(&args1.alock, &args->alock);
		memset(&res1, 0, sizeof(res1));

		stat = nlm_cancel_1(&args1, &res1, client, ext, timo);

		if (stat == RPC_SUCCESS) {
			nlm_convert_to_nlm4_res(res, &res1);
		}

		return (stat);
	}
}