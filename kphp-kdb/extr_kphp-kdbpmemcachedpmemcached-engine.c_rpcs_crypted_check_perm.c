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
struct connection {int our_ip; int remote_ip; } ;

/* Variables and functions */
 int rpcs_default_check_perm (struct connection*) ; 

__attribute__((used)) static int rpcs_crypted_check_perm (struct connection *c) {
  if (c->our_ip == 0x7f000001 && c->remote_ip == 0x7f000001) {
    return 3;
  }
  return rpcs_default_check_perm(c) & -2;
}