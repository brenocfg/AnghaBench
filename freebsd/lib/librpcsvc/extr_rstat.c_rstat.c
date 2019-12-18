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
struct statstime {int dummy; } ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;

/* Variables and functions */
 int /*<<< orphan*/  RSTATPROC_STATS ; 
 int /*<<< orphan*/  RSTATPROG ; 
 int /*<<< orphan*/  RSTATVERS_TIME ; 
 int callrpc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xdr_statstime ; 
 scalar_t__ xdr_void ; 

enum clnt_stat
rstat(char *host, struct statstime *statp)
{
	return (callrpc(host, RSTATPROG, RSTATVERS_TIME, RSTATPROC_STATS,
			(xdrproc_t)xdr_void, (char *) NULL,
			(xdrproc_t)xdr_statstime, (char *) statp));
}