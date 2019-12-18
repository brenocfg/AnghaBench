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
struct TYPE_2__ {int /*<<< orphan*/  tickets; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_swap (int /*<<< orphan*/ *,void*,int) ; 
 TYPE_1__ session_tickets ; 

__attribute__((used)) static void do_swap_register_session_tickets(void *p)
{
    h2o_mem_swap(&session_tickets.tickets, p, sizeof(session_tickets.tickets));
}