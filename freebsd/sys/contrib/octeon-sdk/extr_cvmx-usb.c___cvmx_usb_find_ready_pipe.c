#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {int flags; scalar_t__ next_tx_frame; int split_sc_frame; struct TYPE_8__* next; struct TYPE_8__* head; } ;
typedef  TYPE_1__ cvmx_usb_pipe_t ;
struct TYPE_9__ {TYPE_1__* head; } ;
typedef  TYPE_2__ cvmx_usb_pipe_list_t ;
struct TYPE_10__ {TYPE_1__* active_split; } ;
typedef  TYPE_3__ cvmx_usb_internal_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PREFETCH (TYPE_1__*,int) ; 
 int __CVMX_USB_PIPE_FLAGS_SCHEDULED ; 

__attribute__((used)) static cvmx_usb_pipe_t *__cvmx_usb_find_ready_pipe(cvmx_usb_internal_state_t *usb, cvmx_usb_pipe_list_t *list, uint64_t current_frame)
{
    cvmx_usb_pipe_t *pipe = list->head;
    while (pipe)
    {
        if (!(pipe->flags & __CVMX_USB_PIPE_FLAGS_SCHEDULED) && pipe->head &&
            (pipe->next_tx_frame <= current_frame) &&
            ((pipe->split_sc_frame == -1) || ((((int)current_frame - (int)pipe->split_sc_frame) & 0x7f) < 0x40)) &&
            (!usb->active_split || (usb->active_split == pipe->head)))
        {
            CVMX_PREFETCH(pipe, 128);
            CVMX_PREFETCH(pipe->head, 0);
            return pipe;
        }
        pipe = pipe->next;
    }
    return NULL;
}