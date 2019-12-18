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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  NULLPROC ; 
 scalar_t__ RPC_SUCCESS ; 
 scalar_t__ clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval) ; 
 scalar_t__ xdr_void ; 

void *
rpc_nullproc(CLIENT *clnt)
{
	struct timeval TIMEOUT = {25, 0};

	if (clnt_call(clnt, NULLPROC, (xdrproc_t) xdr_void, NULL,
		(xdrproc_t) xdr_void, NULL, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *) clnt);
}