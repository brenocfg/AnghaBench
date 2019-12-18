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
struct config_str3list {int /*<<< orphan*/  str3; int /*<<< orphan*/  str2; int /*<<< orphan*/  str; struct config_str3list* next; } ;
struct config_file {struct config_str3list* local_zone_overrides; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  lz_enter_override (struct local_zones*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lz_enter_overrides(struct local_zones* zones, struct config_file* cfg)
{
	struct config_str3list* p;
	for(p = cfg->local_zone_overrides; p; p = p->next) {
		if(!lz_enter_override(zones, p->str, p->str2, p->str3,
			LDNS_RR_CLASS_IN))
			return 0;
	}
	return 1;
}