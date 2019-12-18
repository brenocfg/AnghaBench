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
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ cvmx_usb_pipe_t ;
struct TYPE_6__ {TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ cvmx_usb_pipe_list_t ;

/* Variables and functions */

__attribute__((used)) static inline void __cvmx_usb_remove_pipe(cvmx_usb_pipe_list_t *list, cvmx_usb_pipe_t *pipe)
{
    if (list->head == pipe)
    {
        list->head = pipe->next;
        pipe->next = NULL;
        if (list->head)
            list->head->prev = NULL;
        else
            list->tail = NULL;
    }
    else if (list->tail == pipe)
    {
        list->tail = pipe->prev;
        list->tail->next = NULL;
        pipe->prev = NULL;
    }
    else
    {
        pipe->prev->next = pipe->next;
        pipe->next->prev = pipe->prev;
        pipe->prev = NULL;
        pipe->next = NULL;
    }
}