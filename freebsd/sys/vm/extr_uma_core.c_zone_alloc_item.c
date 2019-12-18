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
typedef  int /*<<< orphan*/  uma_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZONE_LOCK (int /*<<< orphan*/ ) ; 
 void* zone_alloc_item_locked (int /*<<< orphan*/ ,void*,int,int) ; 

__attribute__((used)) static void *
zone_alloc_item(uma_zone_t zone, void *udata, int domain, int flags)
{

	ZONE_LOCK(zone);
	return (zone_alloc_item_locked(zone, udata, domain, flags));
}