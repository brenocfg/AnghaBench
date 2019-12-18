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
struct ncpaddr {scalar_t__ ncpaddr_family; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 

int
ncpaddr_isset(const struct ncpaddr *addr)
{
  return addr->ncpaddr_family != AF_UNSPEC;
}