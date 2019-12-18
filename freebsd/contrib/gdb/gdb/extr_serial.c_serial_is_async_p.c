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
struct serial {int /*<<< orphan*/ * async_handler; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/ * async; } ;

/* Variables and functions */

int
serial_is_async_p (struct serial *scb)
{
  return (scb->ops->async != NULL) && (scb->async_handler != NULL);
}