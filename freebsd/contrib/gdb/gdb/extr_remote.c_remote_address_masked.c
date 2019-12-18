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
typedef  int ULONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int remote_address_size ; 

__attribute__((used)) static CORE_ADDR
remote_address_masked (CORE_ADDR addr)
{
  if (remote_address_size > 0
      && remote_address_size < (sizeof (ULONGEST) * 8))
    {
      /* Only create a mask when that mask can safely be constructed
         in a ULONGEST variable. */
      ULONGEST mask = 1;
      mask = (mask << remote_address_size) - 1;
      addr &= mask;
    }
  return addr;
}