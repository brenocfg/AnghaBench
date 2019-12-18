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
 int /*<<< orphan*/  fatal_exit (char*,char const*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rr_nameclass (char const*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct local_zone* local_zones_lookup (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int lz_enter_rr_into_zone (struct local_zone*,char const*) ; 

__attribute__((used)) static int
lz_enter_rr_str(struct local_zones* zones, const char* rr)
{
	uint8_t* rr_name;
	uint16_t rr_class, rr_type;
	size_t len;
	int labs;
	struct local_zone* z;
	int r;
	if(!get_rr_nameclass(rr, &rr_name, &rr_class, &rr_type)) {
		log_err("bad rr %s", rr);
		return 0;
	}
	labs = dname_count_size_labels(rr_name, &len);
	lock_rw_rdlock(&zones->lock);
	z = local_zones_lookup(zones, rr_name, len, labs, rr_class, rr_type);
	if(!z) {
		lock_rw_unlock(&zones->lock);
		fatal_exit("internal error: no zone for rr %s", rr);
	}
	lock_rw_wrlock(&z->lock);
	lock_rw_unlock(&zones->lock);
	free(rr_name);
	r = lz_enter_rr_into_zone(z, rr);
	lock_rw_unlock(&z->lock);
	return r;
}