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
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ifconfig_get_fib (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
print_fib(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	int fib;

	if (ifconfig_get_fib(lifh, ifa->ifa_name, &fib) == 0) {
		printf("\tfib: %d\n", fib);
	} else {
		err(1, "Failed to get interface FIB");
	}
}