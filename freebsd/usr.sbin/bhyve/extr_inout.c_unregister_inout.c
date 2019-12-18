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
struct inout_port {size_t port; scalar_t__ name; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY_IOPORT (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* inout_handlers ; 
 int /*<<< orphan*/  register_default_iohandler (size_t,int /*<<< orphan*/ ) ; 

int
unregister_inout(struct inout_port *iop)
{

	VERIFY_IOPORT(iop->port, iop->size);
	assert(inout_handlers[iop->port].name == iop->name);

	register_default_iohandler(iop->port, iop->size);

	return (0);
}