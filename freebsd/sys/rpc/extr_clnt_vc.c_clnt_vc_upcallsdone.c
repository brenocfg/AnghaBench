#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ct_data {scalar_t__ ct_upcallrefs; TYPE_1__* ct_socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_MTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clnt_vc_upcallsdone(struct ct_data *ct)
{

	SOCKBUF_LOCK_ASSERT(&ct->ct_socket->so_rcv);

	while (ct->ct_upcallrefs > 0)
		(void) msleep(&ct->ct_upcallrefs,
		    SOCKBUF_MTX(&ct->ct_socket->so_rcv), 0, "rpcvcup", 0);
}