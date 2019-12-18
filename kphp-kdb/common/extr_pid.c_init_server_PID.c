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
struct TYPE_2__ {unsigned int ip; int port; } ;

/* Variables and functions */
 TYPE_1__ PID ; 
 int /*<<< orphan*/  init_common_PID () ; 

void init_server_PID (unsigned ip, int port) {
  if (ip && ip != 0x7f000001) {
    PID.ip = ip;
  }
  if (!PID.port) {
    PID.port = port;
  }
  init_common_PID ();
}