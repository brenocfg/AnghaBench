#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_4__ {scalar_t__ necessity; } ;
struct TYPE_5__ {TYPE_1__ cd; } ;
struct ttydevice {int mbits; scalar_t__ carrier_seconds; TYPE_3__ Timer; TYPE_2__ dev; } ;
struct physical {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int CARRIER_LOST ; 
 int CARRIER_OK ; 
 int CARRIER_PENDING ; 
 scalar_t__ CD_NOTREQUIRED ; 
 scalar_t__ Online (struct ttydevice*) ; 
 scalar_t__ TIMER_STOPPED ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 scalar_t__ physical_IsSync (struct physical*) ; 
 int /*<<< orphan*/  tty_StartTimer (struct physical*) ; 

__attribute__((used)) static int
tty_AwaitCarrier(struct physical *p)
{
  struct ttydevice *dev = device2tty(p->handler);

  if (dev->dev.cd.necessity == CD_NOTREQUIRED || physical_IsSync(p))
    return CARRIER_OK;

  if (dev->mbits == -1) {
    if (dev->Timer.state == TIMER_STOPPED) {
      dev->carrier_seconds = 0;
      tty_StartTimer(p);
    }
    return CARRIER_PENDING;			/* Not yet ! */
  }

  return Online(dev) ? CARRIER_OK : CARRIER_LOST;
}