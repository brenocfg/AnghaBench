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
struct serial {void* async_context; int /*<<< orphan*/ * async_handler; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  serial_event_ftype ;
struct TYPE_2__ {int /*<<< orphan*/  (* async ) (struct serial*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct serial*,int /*<<< orphan*/ ) ; 

void
serial_async (struct serial *scb,
	      serial_event_ftype *handler,
	      void *context)
{
  /* Only change mode if there is a need. */
  if ((scb->async_handler == NULL)
      != (handler == NULL))
    scb->ops->async (scb, handler != NULL);
  scb->async_handler = handler;
  scb->async_context = context;
}