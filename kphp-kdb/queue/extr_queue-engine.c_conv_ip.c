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
 char* ip_buff ; 
 int /*<<< orphan*/  ipv6_to_ipv4 () ; 

int conv_ip (void) {
  int dots = 0, i;
  for (i = 0; ip_buff[i] && i < 20; i++) {
    dots += (ip_buff[i] == '.');
  }
  if (dots == 0) {
    if (!ipv6_to_ipv4()) {
      return 0;
    }
  }

  int nums[4], nn = 0, v = 0;
  for (i = 0; ip_buff[i] && i < 20; i++) {
    char c = ip_buff[i];
    if (c == '.') {
      if (nn == 3) {
        return 0;
      }
      nums[nn++] = v;
      v = 0;
    } else if ('0' <= c && c <= '9') {
      v = v * 10 + c - '0';
      if (v > 255) {
        return 0;
      }
    } else {
      return 0;
    }
  }
  nums[nn++] = v;
  return (nums[0] << 24) | (nums[1] << 16) | (nums[2] << 8) | nums[3];
}