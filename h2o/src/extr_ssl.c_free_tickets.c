#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t size; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_1__ session_ticket_vector_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ticket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_tickets(session_ticket_vector_t *tickets)
{
    size_t i;
    for (i = 0; i != tickets->size; ++i)
        free_ticket(tickets->entries[i]);
    free(tickets->entries);
    memset(tickets, 0, sizeof(*tickets));
}