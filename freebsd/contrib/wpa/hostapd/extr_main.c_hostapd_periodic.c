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
struct hapd_interfaces {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_CLEANUP_INTERVAL ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (void*,void*),struct hapd_interfaces*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_for_each_interface (struct hapd_interfaces*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hostapd_periodic_call ; 

__attribute__((used)) static void hostapd_periodic(void *eloop_ctx, void *timeout_ctx)
{
	struct hapd_interfaces *interfaces = eloop_ctx;

	eloop_register_timeout(HOSTAPD_CLEANUP_INTERVAL, 0,
			       hostapd_periodic, interfaces, NULL);
	hostapd_for_each_interface(interfaces, hostapd_periodic_call, NULL);
}