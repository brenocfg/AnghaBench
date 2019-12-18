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
typedef  TYPE_1__* iwdp_iport_t ;
struct TYPE_3__ {char* device_id; int port; char* device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 

void iwdp_log_connect(iwdp_iport_t iport) {
  if (iport->device_id) {
    printf("Connected :%d to %s (%s)\n", iport->port, iport->device_name,
        iport->device_id);
  } else {
    printf("Listing devices on :%d\n", iport->port);
  }
}