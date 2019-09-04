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
 int /*<<< orphan*/  memcpy (int*,scalar_t__,int) ; 
 scalar_t__ packet_end ; 
 scalar_t__ packet_ptr ; 

int rpc_fetch_ints (int *a, int len) {
  if (packet_ptr + len > packet_end) {
    return -1;
  }
  memcpy (a, packet_ptr, len * 4);
  packet_ptr += len;
  return 0;
}