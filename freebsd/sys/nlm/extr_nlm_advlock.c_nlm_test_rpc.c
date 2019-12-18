#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct rpc_callextra {int dummy; } ;
typedef  scalar_t__ rpcvers_t ;
typedef  int /*<<< orphan*/  res1 ;
struct TYPE_18__ {int /*<<< orphan*/  holder; } ;
struct TYPE_19__ {scalar_t__ stat; TYPE_3__ nlm_testrply_u; } ;
struct TYPE_20__ {TYPE_4__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_5__ nlm_testres ;
struct TYPE_21__ {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_6__ nlm_testargs ;
struct TYPE_16__ {int /*<<< orphan*/  holder; } ;
struct TYPE_17__ {int stat; TYPE_1__ nlm4_testrply_u; } ;
struct TYPE_22__ {TYPE_2__ stat; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_7__ nlm4_testres ;
struct TYPE_23__ {int /*<<< orphan*/  alock; int /*<<< orphan*/  exclusive; int /*<<< orphan*/  cookie; } ;
typedef  TYPE_8__ nlm4_testargs ;
typedef  enum nlm4_stats { ____Placeholder_nlm4_stats } nlm4_stats ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 scalar_t__ NLM_VERS4 ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int nlm4_test_4 (TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ *,struct rpc_callextra*,struct timeval) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm4_holder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_convert_to_nlm_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nlm_denied ; 
 int nlm_test_1 (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ *,struct rpc_callextra*,struct timeval) ; 

__attribute__((used)) static enum clnt_stat
nlm_test_rpc(rpcvers_t vers, nlm4_testargs *args, nlm4_testres *res, CLIENT *client,
    struct rpc_callextra *ext, struct timeval timo)
{
	if (vers == NLM_VERS4) {
		return nlm4_test_4(args, res, client, ext, timo);
	} else {
		nlm_testargs args1;
		nlm_testres res1;
		enum clnt_stat stat;

		args1.cookie = args->cookie;
		args1.exclusive = args->exclusive;
		nlm_convert_to_nlm_lock(&args1.alock, &args->alock);
		memset(&res1, 0, sizeof(res1));

		stat = nlm_test_1(&args1, &res1, client, ext, timo);

		if (stat == RPC_SUCCESS) {
			res->cookie = res1.cookie;
			res->stat.stat = (enum nlm4_stats) res1.stat.stat;
			if (res1.stat.stat == nlm_denied)
				nlm_convert_to_nlm4_holder(
					&res->stat.nlm4_testrply_u.holder,
					&res1.stat.nlm_testrply_u.holder);
		}

		return (stat);
	}
}