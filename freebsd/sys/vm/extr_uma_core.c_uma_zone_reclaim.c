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
#define  UMA_RECLAIM_DRAIN 130 
#define  UMA_RECLAIM_DRAIN_CPU 129 
#define  UMA_RECLAIM_TRIM 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pcpu_cache_drain_safe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_trim (int /*<<< orphan*/ ) ; 

void
uma_zone_reclaim(uma_zone_t zone, int req)
{

	switch (req) {
	case UMA_RECLAIM_TRIM:
		zone_trim(zone);
		break;
	case UMA_RECLAIM_DRAIN:
		zone_drain(zone);
		break;
	case UMA_RECLAIM_DRAIN_CPU:
		pcpu_cache_drain_safe(zone);
		zone_drain(zone);
		break;
	default:
		panic("unhandled reclamation request %d", req);
	}
}