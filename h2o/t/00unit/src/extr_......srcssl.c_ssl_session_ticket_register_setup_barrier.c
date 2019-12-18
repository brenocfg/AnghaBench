#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_barrier_t ;
struct TYPE_4__ {int /*<<< orphan*/ * update_thread; } ;
struct TYPE_6__ {TYPE_1__ ticket; } ;
struct TYPE_5__ {int /*<<< orphan*/ * barrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_3__ conf ; 
 int /*<<< orphan*/  h2o_barrier_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 TYPE_2__ session_tickets ; 

void ssl_session_ticket_register_setup_barrier(h2o_barrier_t *barrier)
{
    if (conf.ticket.update_thread == NULL)
        h2o_fatal("ticket-based encryption MUST be enabled when running QUIC");
    assert(session_tickets.barrier == NULL);
    h2o_barrier_add(barrier, 1);
    session_tickets.barrier = barrier;
}