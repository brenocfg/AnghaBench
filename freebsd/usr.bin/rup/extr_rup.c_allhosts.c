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
typedef  int /*<<< orphan*/  statstime ;
typedef  int /*<<< orphan*/  resultproc_t ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int RPC_SUCCESS ; 
 int RPC_TIMEDOUT ; 
 int /*<<< orphan*/  RSTATPROC_STATS ; 
 int /*<<< orphan*/  RSTATPROG ; 
 int /*<<< orphan*/  RSTATVERS_TIME ; 
 int clnt_broadcast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clnt_sperrno (int) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ rstat_reply ; 
 scalar_t__ xdr_statstime ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static void
allhosts(void)
{
	statstime host_stat;
	enum clnt_stat clnt_stat;

	clnt_stat = clnt_broadcast(RSTATPROG, RSTATVERS_TIME, RSTATPROC_STATS,
				   (xdrproc_t)xdr_void, NULL,
				   (xdrproc_t)xdr_statstime, &host_stat,
				   (resultproc_t)rstat_reply);
	if (clnt_stat != RPC_SUCCESS && clnt_stat != RPC_TIMEDOUT)
		errx(1, "%s", clnt_sperrno(clnt_stat));
}