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
struct ncpaddr {int dummy; } ;

/* Variables and functions */
 char const* ncpaddr_ntowa (struct ncpaddr const*) ; 

const char *
ncpaddr_ntoa(const struct ncpaddr *addr)
{
  return ncpaddr_ntowa(addr);
}