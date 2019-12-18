#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ to_async_mask_value; } ;

/* Variables and functions */
 TYPE_1__ current_target ; 
 int /*<<< orphan*/  remote_desc ; 
 scalar_t__ serial_is_async_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
remote_is_async_p (void)
{
  /* We're async whenever the serial device is. */
  return (current_target.to_async_mask_value) && serial_is_async_p (remote_desc);
}