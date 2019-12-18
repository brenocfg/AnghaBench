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

__attribute__((used)) static inline void __cvmx_usb_append_pipe(cvmx_usb_pipe_list_t *list, cvmx_usb_pipe_t *pipe)
{
    pipe->next = NULL;
    pipe->prev = list->tail;
    if (list->tail)
        list->tail->next = pipe;
    else
        list->head = pipe;
    list->tail = pipe;
}