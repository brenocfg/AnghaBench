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

/* Variables and functions */
 int tcp_maximize_buffers ; 
 int /*<<< orphan*/  udp_enabled ; 

int f_parse_function (int val) {
  switch (val) {
  case 'Q':
    tcp_maximize_buffers = 1;
    break;
  case 'U':
    udp_enabled ++;
    break;
  default:
    return -1;
  }
  return 0;
}