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
struct socket {int /*<<< orphan*/  so_rcv; } ;
struct cu_socket {scalar_t__ cs_upcallrefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCKBUF_MTX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clnt_dg_upcallsdone(struct socket *so, struct cu_socket *cs)
{

	SOCKBUF_LOCK_ASSERT(&so->so_rcv);

	while (cs->cs_upcallrefs > 0)
		(void) msleep(&cs->cs_upcallrefs, SOCKBUF_MTX(&so->so_rcv), 0,
		    "rpcdgup", 0);
}