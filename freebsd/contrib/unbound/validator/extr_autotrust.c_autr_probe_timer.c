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
typedef  int time_t ;
struct trust_anchor {int dummy; } ;
struct module_env {int /*<<< orphan*/  scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ autr_permit_small_holddown ; 
 int /*<<< orphan*/  probe_anchor (struct module_env*,struct trust_anchor*) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 
 struct trust_anchor* todo_probe (struct module_env*,int*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 

time_t 
autr_probe_timer(struct module_env* env)
{
	struct trust_anchor* tp;
	time_t next_probe = 3600;
	int num = 0;
	if(autr_permit_small_holddown) next_probe = 1;
	verbose(VERB_ALGO, "autotrust probe timer callback");
	/* while there are still anchors to probe */
	while( (tp = todo_probe(env, &next_probe)) ) {
		/* make a probe for this anchor */
		probe_anchor(env, tp);
		num++;
	}
	regional_free_all(env->scratch);
	if(next_probe == 0)
		return 0; /* no trust points to probe */
	verbose(VERB_ALGO, "autotrust probe timer %d callbacks done", num);
	return next_probe;
}