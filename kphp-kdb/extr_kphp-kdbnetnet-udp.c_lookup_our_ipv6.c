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
 int MAX_OUR_IPS ; 
 int /*<<< orphan*/  fill_outbound_control (int) ; 
 int /*<<< orphan*/  memcmp (int*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,unsigned char const*,int) ; 
 int** our_ipv6 ; 
 int used_our_ipv6 ; 

int lookup_our_ipv6 (const unsigned char ipv6[16]) {
  int i;
  for (i = 1; i <= used_our_ipv6; i += 2) {
    if (!memcmp (our_ipv6[i], ipv6, 16)) {
      return i;
    }
  }
  if (!used_our_ipv6) {
    used_our_ipv6 = 1;
    our_ipv6[1][15] = 1;
    fill_outbound_control (1);
    if (!memcmp (our_ipv6[1], ipv6, 16)) {
      return 1;
    }
  } else if (used_our_ipv6 >= MAX_OUR_IPS - 2) {
    return 0;
  }
  used_our_ipv6 += 2;
  memcpy (our_ipv6[used_our_ipv6], ipv6, 16);
  fill_outbound_control (used_our_ipv6);
  return used_our_ipv6;
}