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
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  rpcproc_t ;
typedef  int /*<<< orphan*/  resultproc_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INITTIME ; 
 int /*<<< orphan*/  WAITTIME ; 
 int rpc_broadcast_exp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

enum clnt_stat
rpc_broadcast(rpcprog_t prog, rpcvers_t vers, rpcproc_t proc, xdrproc_t xargs,
    caddr_t argsp, xdrproc_t xresults, caddr_t resultsp,
    resultproc_t eachresult, const char *nettype)
{
	enum clnt_stat	dummy;

	dummy = rpc_broadcast_exp(prog, vers, proc, xargs, argsp,
		xresults, resultsp, eachresult,
		INITTIME, WAITTIME, nettype);
	return (dummy);
}