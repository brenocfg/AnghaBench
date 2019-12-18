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
typedef  int /*<<< orphan*/  TicketFlags ;

/* Variables and functions */
 scalar_t__ TicketFlags2int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmp_TicketFlags (void *a, void *b)
{
    TicketFlags *aa = a;
    TicketFlags *ab = b;

    return TicketFlags2int(*aa) != TicketFlags2int(*ab);
}