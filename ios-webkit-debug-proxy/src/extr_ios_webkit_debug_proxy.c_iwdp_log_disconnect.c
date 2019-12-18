#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* iwdp_iport_t ;
struct TYPE_5__ {int port; char* device_name; char* device_id; TYPE_1__* iwi; } ;
struct TYPE_4__ {scalar_t__ connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void iwdp_log_disconnect(iwdp_iport_t iport) {
  if (iport->iwi && iport->iwi->connected) {
    printf("Disconnected :%d from %s (%s)\n", iport->port,
        iport->device_name, iport->device_id);
  } else {
    printf("Unable to connect to %s (%s)\n  Please"
        " verify that Settings > Safari > Advanced > Web Inspector = ON\n",
        iport->device_name, iport->device_id);
  }
}