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
struct svc_req {int dummy; } ;
struct rpc_msg {int dummy; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;

/* Variables and functions */
 int AUTH_REJECTEDCRED ; 

enum auth_stat 
_svcauth_short(struct svc_req *rqst, struct rpc_msg *msg)
{
	return (AUTH_REJECTEDCRED);
}