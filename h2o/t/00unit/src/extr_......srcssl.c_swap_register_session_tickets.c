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
typedef  int /*<<< orphan*/  session_ticket_vector_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_swap_register_session_tickets ; 
 int /*<<< orphan*/  register_session_tickets (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void swap_register_session_tickets(session_ticket_vector_t *p)
{
    register_session_tickets(do_swap_register_session_tickets, p);
}