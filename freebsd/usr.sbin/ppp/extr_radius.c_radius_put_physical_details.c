#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  rad; } ;
struct radius {int port_id_type; TYPE_5__ cx; } ;
struct physical {TYPE_4__* dl; TYPE_1__* handler; } ;
struct TYPE_9__ {TYPE_3__* bundle; } ;
struct TYPE_8__ {int unit; TYPE_2__* iface; } ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {int type; } ;

/* Variables and functions */
#define  ATM_DEVICE 139 
#define  ETHER_DEVICE 138 
#define  EXEC_DEVICE 137 
#define  I4B_DEVICE 136 
 int /*<<< orphan*/  LogERROR ; 
#define  NG_DEVICE 135 
 int RAD_ASYNC ; 
 int RAD_ETHERNET ; 
 int RAD_ISDN_SYNC ; 
 int /*<<< orphan*/  RAD_NAS_PORT ; 
 int /*<<< orphan*/  RAD_NAS_PORT_TYPE ; 
 int RAD_VIRTUAL ; 
#define  RPI_DEFAULT 134 
#define  RPI_IFNUM 133 
#define  RPI_PID 132 
#define  RPI_TUNNUM 131 
#define  TCP_DEVICE 130 
#define  TTY_DEVICE 129 
#define  UDP_DEVICE 128 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int physical_Slot (struct physical*) ; 
 int /*<<< orphan*/  rad_close (int /*<<< orphan*/ ) ; 
 scalar_t__ rad_put_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rad_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
radius_put_physical_details(struct radius *rad, struct physical *p)
{
  int slot, type;

  type = RAD_VIRTUAL;
  if (p->handler)
    switch (p->handler->type) {
      case I4B_DEVICE:
        type = RAD_ISDN_SYNC;
        break;

      case TTY_DEVICE:
        type = RAD_ASYNC;
        break;

      case ETHER_DEVICE:
        type = RAD_ETHERNET;
        break;

      case TCP_DEVICE:
      case UDP_DEVICE:
      case EXEC_DEVICE:
      case ATM_DEVICE:
      case NG_DEVICE:
        type = RAD_VIRTUAL;
        break;
    }

  if (rad_put_int(rad->cx.rad, RAD_NAS_PORT_TYPE, type) != 0) {
    log_Printf(LogERROR, "rad_put: rad_put_int: %s\n", rad_strerror(rad->cx.rad));
    rad_close(rad->cx.rad);
    return 0;
  }

  switch (rad->port_id_type) {
    case RPI_PID:
      slot = (int)getpid();
      break;
    case RPI_IFNUM:
      slot = p->dl->bundle->iface->index;
      break;
    case RPI_TUNNUM:
      slot = p->dl->bundle->unit;
      break;
    case RPI_DEFAULT:
    default:
      slot = physical_Slot(p);
      break;
  }
  
  if (slot >= 0)
    if (rad_put_int(rad->cx.rad, RAD_NAS_PORT, slot) != 0) {
      log_Printf(LogERROR, "rad_put: rad_put_int: %s\n", rad_strerror(rad->cx.rad));
      rad_close(rad->cx.rad);
      return 0;
    }

  return 1;
}