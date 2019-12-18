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
struct mac_acl_entry {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  macaddr ;

/* Variables and functions */
 int os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int hostapd_acl_comp(const void *a, const void *b)
{
	const struct mac_acl_entry *aa = a;
	const struct mac_acl_entry *bb = b;
	return os_memcmp(aa->addr, bb->addr, sizeof(macaddr));
}