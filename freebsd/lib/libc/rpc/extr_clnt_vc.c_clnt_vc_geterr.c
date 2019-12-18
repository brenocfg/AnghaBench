#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_err {int dummy; } ;
struct ct_data {struct rpc_err ct_error; } ;
struct TYPE_3__ {scalar_t__ cl_private; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clnt_vc_geterr(CLIENT *cl, struct rpc_err *errp)
{
	struct ct_data *ct;

	assert(cl != NULL);
	assert(errp != NULL);

	ct = (struct ct_data *) cl->cl_private;
	*errp = ct->ct_error;
}