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
struct TYPE_3__ {scalar_t__ pid_toggle; } ;
typedef  TYPE_1__ cvmx_usb_pipe_t ;

/* Variables and functions */

__attribute__((used)) static inline int __cvmx_usb_get_data_pid(cvmx_usb_pipe_t *pipe)
{
    if (pipe->pid_toggle)
        return 2; /* Data1 */
    else
        return 0; /* Data0 */
}