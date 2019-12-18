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
struct svc_req {int /*<<< orphan*/  rq_verf; } ;
struct rpc_msg {int dummy; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;

/* Variables and functions */
 int AUTH_OK ; 
 int /*<<< orphan*/  _null_auth ; 

enum auth_stat
_svcauth_null(struct svc_req *rqst, struct rpc_msg *msg)
{

	rqst->rq_verf = _null_auth;
	return (AUTH_OK);
}