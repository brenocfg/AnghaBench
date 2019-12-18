#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int cvmx_usb_transfer_t ;
typedef  int /*<<< orphan*/  cvmx_usb_state_t ;
typedef  int cvmx_usb_speed_t ;
struct TYPE_10__ {int flags; int device_addr; int endpoint_num; int device_speed; int max_packet; int transfer_type; int transfer_dir; int interval; int next_tx_frame; int multi_count; int hub_device_addr; int hub_port; int split_sc_frame; scalar_t__ pid_toggle; } ;
typedef  TYPE_1__ cvmx_usb_pipe_t ;
typedef  int cvmx_usb_pipe_flags_t ;
struct TYPE_12__ {TYPE_1__* head; } ;
struct TYPE_11__ {int frame_number; int /*<<< orphan*/  idle_pipes; TYPE_3__ free_pipes; } ;
typedef  TYPE_2__ cvmx_usb_internal_state_t ;
typedef  int cvmx_usb_direction_t ;

/* Variables and functions */
 int CVMX_USB_DIRECTION_IN ; 
 int CVMX_USB_DIRECTION_OUT ; 
 int /*<<< orphan*/  CVMX_USB_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_USB_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_USB_LOG_PARAM (char*,int) ; 
 int /*<<< orphan*/  CVMX_USB_NO_MEMORY ; 
 int /*<<< orphan*/  CVMX_USB_RETURN (int /*<<< orphan*/ ) ; 
 int CVMX_USB_SPEED_HIGH ; 
 int CVMX_USB_SPEED_LOW ; 
 int CVMX_USB_TRANSFER_BULK ; 
 int CVMX_USB_TRANSFER_CONTROL ; 
 int CVMX_USB_TRANSFER_INTERRUPT ; 
 int MAX_USB_ADDRESS ; 
 int MAX_USB_ENDPOINT ; 
 int MAX_USB_HUB_PORT ; 
 int __CVMX_USB_PIPE_FLAGS_NEED_PING ; 
 int __CVMX_USB_PIPE_FLAGS_OPEN ; 
 int /*<<< orphan*/  __cvmx_usb_append_pipe (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  __cvmx_usb_get_pipe_handle (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ __cvmx_usb_pipe_needs_split (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  __cvmx_usb_remove_pipe (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ cvmx_unlikely (int) ; 

int cvmx_usb_open_pipe(cvmx_usb_state_t *state, cvmx_usb_pipe_flags_t flags,
                       int device_addr, int endpoint_num,
                       cvmx_usb_speed_t device_speed, int max_packet,
                       cvmx_usb_transfer_t transfer_type,
                       cvmx_usb_direction_t transfer_dir, int interval,
                       int multi_count, int hub_device_addr, int hub_port)
{
    cvmx_usb_pipe_t *pipe;
    cvmx_usb_internal_state_t *usb = (cvmx_usb_internal_state_t*)state;

    CVMX_USB_LOG_CALLED();
    CVMX_USB_LOG_PARAM("%p", state);
    CVMX_USB_LOG_PARAM("0x%x", flags);
    CVMX_USB_LOG_PARAM("%d", device_addr);
    CVMX_USB_LOG_PARAM("%d", endpoint_num);
    CVMX_USB_LOG_PARAM("%d", device_speed);
    CVMX_USB_LOG_PARAM("%d", max_packet);
    CVMX_USB_LOG_PARAM("%d", transfer_type);
    CVMX_USB_LOG_PARAM("%d", transfer_dir);
    CVMX_USB_LOG_PARAM("%d", interval);
    CVMX_USB_LOG_PARAM("%d", multi_count);
    CVMX_USB_LOG_PARAM("%d", hub_device_addr);
    CVMX_USB_LOG_PARAM("%d", hub_port);

    if (cvmx_unlikely((device_addr < 0) || (device_addr > MAX_USB_ADDRESS)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((endpoint_num < 0) || (endpoint_num > MAX_USB_ENDPOINT)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(device_speed > CVMX_USB_SPEED_LOW))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((max_packet <= 0) || (max_packet > 1024)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(transfer_type > CVMX_USB_TRANSFER_INTERRUPT))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((transfer_dir != CVMX_USB_DIRECTION_OUT) &&
        (transfer_dir != CVMX_USB_DIRECTION_IN)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(interval < 0))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((transfer_type == CVMX_USB_TRANSFER_CONTROL) && interval))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely(multi_count < 0))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((device_speed != CVMX_USB_SPEED_HIGH) &&
        (multi_count != 0)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((hub_device_addr < 0) || (hub_device_addr > MAX_USB_ADDRESS)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);
    if (cvmx_unlikely((hub_port < 0) || (hub_port > MAX_USB_HUB_PORT)))
        CVMX_USB_RETURN(CVMX_USB_INVALID_PARAM);

    /* Find a free pipe */
    pipe = usb->free_pipes.head;
    if (!pipe)
        CVMX_USB_RETURN(CVMX_USB_NO_MEMORY);
    __cvmx_usb_remove_pipe(&usb->free_pipes, pipe);
    pipe->flags = flags | __CVMX_USB_PIPE_FLAGS_OPEN;
    if ((device_speed == CVMX_USB_SPEED_HIGH) &&
        (transfer_dir == CVMX_USB_DIRECTION_OUT) &&
        (transfer_type == CVMX_USB_TRANSFER_BULK))
        pipe->flags |= __CVMX_USB_PIPE_FLAGS_NEED_PING;
    pipe->device_addr = device_addr;
    pipe->endpoint_num = endpoint_num;
    pipe->device_speed = device_speed;
    pipe->max_packet = max_packet;
    pipe->transfer_type = transfer_type;
    pipe->transfer_dir = transfer_dir;
    /* All pipes use interval to rate limit NAK processing. Force an interval
        if one wasn't supplied */
    if (!interval)
        interval = 1;
    if (__cvmx_usb_pipe_needs_split(usb, pipe))
    {
        pipe->interval = interval*8;
        /* Force start splits to be schedule on uFrame 0 */
        pipe->next_tx_frame = ((usb->frame_number+7)&~7) + pipe->interval;
    }
    else
    {
        pipe->interval = interval;
        pipe->next_tx_frame = usb->frame_number + pipe->interval;
    }
    pipe->multi_count = multi_count;
    pipe->hub_device_addr = hub_device_addr;
    pipe->hub_port = hub_port;
    pipe->pid_toggle = 0;
    pipe->split_sc_frame = -1;
    __cvmx_usb_append_pipe(&usb->idle_pipes, pipe);

    /* We don't need to tell the hardware about this pipe yet since
        it doesn't have any submitted requests */

    CVMX_USB_RETURN(__cvmx_usb_get_pipe_handle(usb, pipe));
}