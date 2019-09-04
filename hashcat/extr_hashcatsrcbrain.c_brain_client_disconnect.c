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
struct TYPE_3__ {int brain_link_client_fd; } ;
typedef  TYPE_1__ hc_device_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 

void brain_client_disconnect (hc_device_param_t *device_param)
{
  if (device_param->brain_link_client_fd > 2)
  {
    close (device_param->brain_link_client_fd);
  }

  device_param->brain_link_client_fd = -1;
}