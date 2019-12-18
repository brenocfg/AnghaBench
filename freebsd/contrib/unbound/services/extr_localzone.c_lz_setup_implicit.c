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
typedef  scalar_t__ uint16_t ;
struct local_zones {int /*<<< orphan*/  lock; } ;
struct local_zone {int /*<<< orphan*/  lock; } ;
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
struct config_file {struct config_strlist* local_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  dname_lab_cmp (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  dname_remove_labels (int /*<<< orphan*/ **,size_t*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rr_nameclass (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  init_parents (struct local_zones*) ; 
 int /*<<< orphan*/  local_zone_transparent ; 
 int /*<<< orphan*/  local_zones_lookup (struct local_zones*,int /*<<< orphan*/ *,size_t,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct local_zone* lz_enter_zone_dname (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * memdup (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
lz_setup_implicit(struct local_zones* zones, struct config_file* cfg)
{
	/* walk over all items that have no parent zone and find
	 * the name that covers them all (could be the root) and
	 * add that as a transparent zone */
	struct config_strlist* p;
	int have_name = 0;
	int have_other_classes = 0;
	uint16_t dclass = 0;
	uint8_t* nm = 0;
	size_t nmlen = 0;
	int nmlabs = 0;
	int match = 0; /* number of labels match count */

	init_parents(zones); /* to enable local_zones_lookup() */
	for(p = cfg->local_data; p; p = p->next) {
		uint8_t* rr_name;
		uint16_t rr_class, rr_type;
		size_t len;
		int labs;
		if(!get_rr_nameclass(p->str, &rr_name, &rr_class, &rr_type)) {
			log_err("Bad local-data RR %s", p->str);
			return 0;
		}
		labs = dname_count_size_labels(rr_name, &len);
		lock_rw_rdlock(&zones->lock);
		if(!local_zones_lookup(zones, rr_name, len, labs, rr_class,
			rr_type)) {
			if(!have_name) {
				dclass = rr_class;
				nm = rr_name;
				nmlen = len;
				nmlabs = labs;
				match = labs;
				have_name = 1;
			} else {
				int m;
				if(rr_class != dclass) {
					/* process other classes later */
					free(rr_name);
					have_other_classes = 1;
					lock_rw_unlock(&zones->lock);
					continue;
				}
				/* find smallest shared topdomain */
				(void)dname_lab_cmp(nm, nmlabs, 
					rr_name, labs, &m);
				free(rr_name);
				if(m < match)
					match = m;
			}
		} else free(rr_name);
		lock_rw_unlock(&zones->lock);
	}
	if(have_name) {
		uint8_t* n2;
		struct local_zone* z;
		/* allocate zone of smallest shared topdomain to contain em */
		n2 = nm;
		dname_remove_labels(&n2, &nmlen, nmlabs - match);
		n2 = memdup(n2, nmlen);
		free(nm);
		if(!n2) {
			log_err("out of memory");
			return 0;
		}
		log_nametypeclass(VERB_ALGO, "implicit transparent local-zone", 
			n2, 0, dclass);
		if(!(z=lz_enter_zone_dname(zones, n2, nmlen, match, 
			local_zone_transparent, dclass))) {
			return 0;
		}
		lock_rw_unlock(&z->lock);
	}
	if(have_other_classes) { 
		/* restart to setup other class */
		return lz_setup_implicit(zones, cfg);
	}
	return 1;
}