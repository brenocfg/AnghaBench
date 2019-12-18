#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  TYPE_1__* uma_keg_t ;
typedef  int /*<<< orphan*/  uma_free ;
struct TYPE_5__ {int /*<<< orphan*/  uk_freef; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KEG_GET (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  KEG_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  KEG_UNLOCK (TYPE_1__*) ; 

void
uma_zone_set_freef(uma_zone_t zone, uma_free freef)
{
	uma_keg_t keg;

	KEG_GET(zone, keg);
	KASSERT(keg != NULL, ("uma_zone_set_freef: Invalid zone type"));
	KEG_LOCK(keg);
	keg->uk_freef = freef;
	KEG_UNLOCK(keg);
}