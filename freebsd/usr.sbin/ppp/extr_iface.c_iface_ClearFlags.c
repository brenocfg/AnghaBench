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
 int /*<<< orphan*/  IFACE_DELFLAGS ; 
 int iface_ChangeFlags (char const*,int,int /*<<< orphan*/ ) ; 

int
iface_ClearFlags(const char *ifname, int flags)
{
  return iface_ChangeFlags(ifname, flags, IFACE_DELFLAGS);
}