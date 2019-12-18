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
struct netmap_adapter {scalar_t__ nm_register; } ;

/* Variables and functions */
 scalar_t__ generic_netmap_register ; 

int
na_is_generic(struct netmap_adapter *na)
{
	return na->nm_register == generic_netmap_register;
}