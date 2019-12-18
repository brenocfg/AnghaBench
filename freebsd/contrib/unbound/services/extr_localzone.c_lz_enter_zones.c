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
struct local_zones {int dummy; } ;
struct local_zone {int /*<<< orphan*/  lock; } ;
struct config_str2list {int /*<<< orphan*/  str2; int /*<<< orphan*/  str; struct config_str2list* next; } ;
struct config_file {struct config_str2list* local_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 struct local_zone* lz_enter_zone (struct local_zones*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lz_enter_zones(struct local_zones* zones, struct config_file* cfg)
{
	struct config_str2list* p;
	struct local_zone* z;
	for(p = cfg->local_zones; p; p = p->next) {
		if(!(z=lz_enter_zone(zones, p->str, p->str2, 
			LDNS_RR_CLASS_IN)))
			return 0;
		lock_rw_unlock(&z->lock);
	}
	return 1;
}