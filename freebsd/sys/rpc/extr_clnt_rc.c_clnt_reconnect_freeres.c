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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct rc_data {int /*<<< orphan*/  rc_client; } ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {scalar_t__ cl_private; } ;
typedef  TYPE_1__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CLNT_FREERES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bool_t
clnt_reconnect_freeres(CLIENT *cl, xdrproc_t xdr_res, void *res_ptr)
{
	struct rc_data *rc = (struct rc_data *)cl->cl_private;

	return (CLNT_FREERES(rc->rc_client, xdr_res, res_ptr));
}