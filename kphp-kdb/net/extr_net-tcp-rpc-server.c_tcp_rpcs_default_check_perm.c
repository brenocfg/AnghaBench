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
struct connection {int flags; int remote_ip; int our_ip; scalar_t__ remote_ipv6; scalar_t__ our_ipv6; } ;

/* Variables and functions */
 int C_IPV6 ; 
 scalar_t__ aes_initialized ; 
 scalar_t__ is_ipv6_localhost (scalar_t__) ; 

int tcp_rpcs_default_check_perm (struct connection *c) {
  int ipxor = -1, mask = -1;
  if (c->flags & C_IPV6) {
    if (is_ipv6_localhost (c->our_ipv6) && is_ipv6_localhost (c->remote_ipv6)) {
      ipxor = 0;
    } else if (*((int *)(c->our_ipv6)) != *((int *)(c->remote_ipv6))) {
      return 0;
    } else {
      ipxor = ((int *)(c->our_ipv6))[1] ^ ((int *)(c->remote_ipv6))[1];
      mask = 0xffff;
    }
  } else {
    if ((c->remote_ip & 0xff000000) != 0x0a000000 && (c->remote_ip & 0xff000000) != 0x7f000000) {
      return 0;
    }
    ipxor = (c->our_ip ^ c->remote_ip);
    mask = 0xffff0000;
  }
  if (aes_initialized <= 0) {
    return (ipxor & mask) ? 0 : 1;
  }
  return (ipxor & mask) ? 2 : 3;
}