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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct dyn_parent {scalar_t__ expire; void* hashval; int /*<<< orphan*/  rulenum; void* ruleid; void* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_dyn_parent_zone ; 
 scalar_t__ V_dyn_short_lifetime ; 
 scalar_t__ last_log ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_uptime ; 
 struct dyn_parent* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dyn_parent *
dyn_alloc_parent(void *parent, uint32_t ruleid, uint16_t rulenum,
    uint32_t hashval)
{
	struct dyn_parent *limit;

	limit = uma_zalloc(V_dyn_parent_zone, M_NOWAIT | M_ZERO);
	if (limit == NULL) {
		if (last_log != time_uptime) {
			last_log = time_uptime;
			log(LOG_DEBUG,
			    "ipfw: Cannot allocate parent dynamic state, "
			    "consider increasing "
			    "net.inet.ip.fw.dyn_parent_max\n");
		}
		return (NULL);
	}

	limit->parent = parent;
	limit->ruleid = ruleid;
	limit->rulenum = rulenum;
	limit->hashval = hashval;
	limit->expire = time_uptime + V_dyn_short_lifetime;
	return (limit);
}