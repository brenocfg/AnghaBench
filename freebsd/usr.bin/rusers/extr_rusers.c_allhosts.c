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
typedef  int /*<<< orphan*/  utmpidlearr ;
typedef  int /*<<< orphan*/  up ;
typedef  int /*<<< orphan*/  resultproc_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int RPC_TIMEDOUT ; 
 int /*<<< orphan*/  RUSERSPROC_NAMES ; 
 int /*<<< orphan*/  RUSERSPROG ; 
 int /*<<< orphan*/  RUSERSVERS_IDLE ; 
 int clnt_broadcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_sperrno (int) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rusers_reply ; 
 scalar_t__ xdr_utmpidlearr ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
allhosts(void)
{
	utmpidlearr up;
	enum clnt_stat clnt_stat;

	memset(&up, 0, sizeof(up));
	clnt_stat = clnt_broadcast(RUSERSPROG, RUSERSVERS_IDLE,
	    RUSERSPROC_NAMES, (xdrproc_t)xdr_void, NULL,
	    (xdrproc_t)xdr_utmpidlearr, (char *)&up,
	    (resultproc_t)rusers_reply);
	if (clnt_stat != RPC_SUCCESS && clnt_stat != RPC_TIMEDOUT)
		errx(1, "%s", clnt_sperrno(clnt_stat));
}