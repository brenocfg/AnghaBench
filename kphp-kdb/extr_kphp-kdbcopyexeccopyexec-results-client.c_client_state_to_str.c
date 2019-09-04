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
typedef  enum client_state { ____Placeholder_client_state } client_state ;

/* Variables and functions */
#define  st_data_sent 131 
#define  st_handshake_received 130 
#define  st_handshake_sent 129 
#define  st_startup 128 

char *client_state_to_str (enum client_state s) {
  switch (s) {
    case st_startup: return "startup";
    case st_handshake_sent: return "handshake_sent";
    case st_handshake_received: return "handshake_received";
    case st_data_sent: return "data_sent";
    default: return "unknown";
  }
}