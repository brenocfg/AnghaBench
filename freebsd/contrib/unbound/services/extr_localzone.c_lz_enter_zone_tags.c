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
struct config_strbytelist {int /*<<< orphan*/  str2len; int /*<<< orphan*/  str2; int /*<<< orphan*/  str; struct config_strbytelist* next; } ;
struct config_file {struct config_strbytelist* local_zone_tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  lz_enter_zone_tag (struct local_zones*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
lz_enter_zone_tags(struct local_zones* zones, struct config_file* cfg)
{
	struct config_strbytelist* p;
	int c = 0;
	for(p = cfg->local_zone_tags; p; p = p->next) {
		if(!lz_enter_zone_tag(zones, p->str, p->str2, p->str2len,
			LDNS_RR_CLASS_IN))
			return 0;
		c++;
	}
	if(c) verbose(VERB_ALGO, "applied tags to %d local zones", c);
	return 1;
}