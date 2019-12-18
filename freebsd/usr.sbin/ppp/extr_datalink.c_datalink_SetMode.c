#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ run; } ;
struct datalink {scalar_t__ state; scalar_t__ reconnect_tries; TYPE_2__* physical; TYPE_1__ script; } ;
struct TYPE_4__ {int type; } ;

/* Variables and functions */
 scalar_t__ DATALINK_READY ; 
 int PHYS_BACKGROUND ; 
 int PHYS_DDIAL ; 
 int PHYS_DEDICATED ; 
 int PHYS_DIRECT ; 
 int PHYS_FOREGROUND ; 
 int /*<<< orphan*/  datalink_Up (struct datalink*,int,int) ; 
 int /*<<< orphan*/  physical_SetMode (TYPE_2__*,int) ; 

int
datalink_SetMode(struct datalink *dl, int mode)
{
  if (!physical_SetMode(dl->physical, mode))
    return 0;
  if (dl->physical->type & (PHYS_DIRECT|PHYS_DEDICATED))
    dl->script.run = 0;
  if (dl->physical->type == PHYS_DIRECT)
    dl->reconnect_tries = 0;
  if (mode & (PHYS_DDIAL|PHYS_BACKGROUND|PHYS_FOREGROUND) &&
      dl->state <= DATALINK_READY)
    datalink_Up(dl, 1, 1);
  return 1;
}