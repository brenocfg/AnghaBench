#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/ * prev; scalar_t__ flags; } ;
typedef  TYPE_1__ cvmx_usb_transaction_t ;
struct TYPE_6__ {TYPE_1__* free_transaction_tail; TYPE_1__* free_transaction_head; } ;
typedef  TYPE_2__ cvmx_usb_internal_state_t ;

/* Variables and functions */

__attribute__((used)) static inline void __cvmx_usb_free_transaction(cvmx_usb_internal_state_t *usb,
                                        cvmx_usb_transaction_t *transaction)
{
    transaction->flags = 0;
    transaction->prev = NULL;
    transaction->next = NULL;
    if (usb->free_transaction_tail)
        usb->free_transaction_tail->next = transaction;
    else
        usb->free_transaction_head = transaction;
    usb->free_transaction_tail = transaction;
}