#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cvmx_usb_pipe_t ;
struct TYPE_3__ {scalar_t__ pipe; } ;
typedef  TYPE_1__ cvmx_usb_internal_state_t ;

/* Variables and functions */

__attribute__((used)) static inline int __cvmx_usb_get_pipe_handle(cvmx_usb_internal_state_t *usb,
                                        cvmx_usb_pipe_t *pipe)
{
    return ((unsigned long)pipe - (unsigned long)usb->pipe) / sizeof(*pipe);
}