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
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;
struct config_file {struct config_strlist* local_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  lz_enter_rr_str (struct local_zones*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lz_enter_data(struct local_zones* zones, struct config_file* cfg)
{
	struct config_strlist* p;
	for(p = cfg->local_data; p; p = p->next) {
		if(!lz_enter_rr_str(zones, p->str))
			return 0;
	}
	return 1;
}