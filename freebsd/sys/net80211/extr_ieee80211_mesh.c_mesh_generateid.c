#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct ieee80211vap {TYPE_1__* iv_ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 
 int /*<<< orphan*/  ieee80211_iterate_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mesh_checkid ; 

__attribute__((used)) static uint32_t
mesh_generateid(struct ieee80211vap *vap)
{
	int maxiter = 4;
	uint16_t r;

	do {
		get_random_bytes(&r, 2);
		ieee80211_iterate_nodes(&vap->iv_ic->ic_sta, mesh_checkid, &r);
		maxiter--;
	} while (r == 0 && maxiter > 0);
	return r;
}