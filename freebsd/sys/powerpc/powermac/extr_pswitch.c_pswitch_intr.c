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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  KDB_WHY_POWERPC ; 
 int /*<<< orphan*/  device_get_nameunit (scalar_t__) ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pswitch_intr(void *arg)
{
	device_t	dev;

	dev = (device_t)arg;

	kdb_enter(KDB_WHY_POWERPC, device_get_nameunit(dev));
	return (FILTER_HANDLED);
}