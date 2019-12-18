#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;

/* Variables and functions */

const char *
State2Nam(u_int state)
{
  static const char * const StateNames[] = {
    "Initial", "Starting", "Closed", "Stopped", "Closing", "Stopping",
    "Req-Sent", "Ack-Rcvd", "Ack-Sent", "Opened",
  };

  if (state >= sizeof StateNames / sizeof StateNames[0])
    return "unknown";
  return StateNames[state];
}