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
struct TYPE_3__ {scalar_t__ ipv6; scalar_t__ mask; } ;
typedef  TYPE_1__ dns_network6_t ;

/* Variables and functions */

__attribute__((used)) static int dns_check_ip6 (dns_network6_t *N, unsigned char *ipv6) {
  unsigned long long *m = (unsigned long long *) N->mask;
  unsigned long long *a = (unsigned long long *) N->ipv6;
  unsigned long long *b = (unsigned long long *) ipv6;
  if (((a[0] ^ b[0]) & m[0]) | ((a[1] ^ b[1]) & m[1])) {
    return -1;
  }
  return 0;
}