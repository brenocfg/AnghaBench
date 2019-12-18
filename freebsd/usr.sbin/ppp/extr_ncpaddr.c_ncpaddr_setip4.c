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
struct in_addr {int dummy; } ;
struct ncpaddr {struct in_addr ncpaddr_ip4addr; int /*<<< orphan*/  ncpaddr_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 

void
ncpaddr_setip4(struct ncpaddr *addr, struct in_addr ip)
{
  addr->ncpaddr_family = AF_INET;
  addr->ncpaddr_ip4addr = ip;
}