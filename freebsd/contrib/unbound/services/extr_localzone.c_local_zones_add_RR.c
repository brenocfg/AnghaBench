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
struct local_zones {int /*<<< orphan*/  lock; } ;
struct local_zone {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rr_nameclass (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_zone_transparent ; 
 struct local_zone* local_zones_add_zone (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct local_zone* local_zones_lookup (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int lz_enter_rr_into_zone (struct local_zone*,char const*) ; 

int
local_zones_add_RR(struct local_zones* zones, const char* rr)
{
	uint8_t* rr_name;
	uint16_t rr_class, rr_type;
	size_t len;
	int labs;
	struct local_zone* z;
	int r;
	if(!get_rr_nameclass(rr, &rr_name, &rr_class, &rr_type)) {
		return 0;
	}
	labs = dname_count_size_labels(rr_name, &len);
	/* could first try readlock then get writelock if zone does not exist,
	 * but we do not add enough RRs (from multiple threads) to optimize */
	lock_rw_wrlock(&zones->lock);
	z = local_zones_lookup(zones, rr_name, len, labs, rr_class, rr_type);
	if(!z) {
		z = local_zones_add_zone(zones, rr_name, len, labs, rr_class,
			local_zone_transparent);
		if(!z) {
			lock_rw_unlock(&zones->lock);
			return 0;
		}
	} else {
		free(rr_name);
	}
	lock_rw_wrlock(&z->lock);
	lock_rw_unlock(&zones->lock);
	r = lz_enter_rr_into_zone(z, rr);
	lock_rw_unlock(&z->lock);
	return r;
}