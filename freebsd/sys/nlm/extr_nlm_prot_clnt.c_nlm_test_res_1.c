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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int dummy; } ;
struct rpc_callextra {int dummy; } ;
typedef  int /*<<< orphan*/  nlm_testres ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int CLNT_CALL_EXT (int /*<<< orphan*/ *,struct rpc_callextra*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval) ; 
 int /*<<< orphan*/  NLM_TEST_RES ; 
 scalar_t__ xdr_nlm_testres ; 
 scalar_t__ xdr_void ; 

enum clnt_stat 
nlm_test_res_1(nlm_testres *argp, void *clnt_res, CLIENT *clnt, struct rpc_callextra *ext, struct timeval timo)
{
	return (CLNT_CALL_EXT(clnt, ext, NLM_TEST_RES,
		(xdrproc_t) xdr_nlm_testres, (caddr_t) argp,
		(xdrproc_t) xdr_void, (caddr_t) clnt_res,
		timo));
}