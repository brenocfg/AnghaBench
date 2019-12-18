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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct auth_zones {int /*<<< orphan*/  lock; } ;
struct auth_zone {int /*<<< orphan*/  lock; int /*<<< orphan*/  for_upstream; scalar_t__ fallback_enabled; } ;

/* Variables and functions */
 struct auth_zone* auth_zone_find (struct auth_zones*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 

int auth_zones_can_fallback(struct auth_zones* az, uint8_t* nm, size_t nmlen,
	uint16_t dclass)
{
	int r;
	struct auth_zone* z;
	lock_rw_rdlock(&az->lock);
	z = auth_zone_find(az, nm, nmlen, dclass);
	if(!z) {
		lock_rw_unlock(&az->lock);
		/* no such auth zone, fallback */
		return 1;
	}
	lock_rw_rdlock(&z->lock);
	lock_rw_unlock(&az->lock);
	r = z->fallback_enabled || (!z->for_upstream);
	lock_rw_unlock(&z->lock);
	return r;
}