#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sin6_family; } ;
struct TYPE_6__ {TYPE_2__ address6; } ;
struct TYPE_8__ {int /*<<< orphan*/  is_internal; TYPE_1__ address; } ;
typedef  TYPE_3__ uv_interface_address_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  uv_free_interface_addresses (TYPE_3__*,int) ; 
 scalar_t__ uv_interface_addresses (TYPE_3__**,int*) ; 

__attribute__((used)) static int can_ipv6_external(void) {
  uv_interface_address_t* addr;
  int supported;
  int count;
  int i;

  if (uv_interface_addresses(&addr, &count))
    return 0;  /* Assume no IPv6 support on failure. */

  supported = 0;
  for (i = 0; supported == 0 && i < count; i += 1)
    supported = (AF_INET6 == addr[i].address.address6.sin6_family &&
                 !addr[i].is_internal);

  uv_free_interface_addresses(addr, count);
  return supported;
}