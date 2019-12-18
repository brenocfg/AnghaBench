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
struct cgroup_subsys_state {int dummy; } ;
struct blkcg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcg_cgwb_put (struct blkcg*) ; 
 struct blkcg* css_to_blkcg (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  wb_blkcg_offline (struct blkcg*) ; 

__attribute__((used)) static void blkcg_css_offline(struct cgroup_subsys_state *css)
{
	struct blkcg *blkcg = css_to_blkcg(css);

	/* this prevents anyone from attaching or migrating to this blkcg */
	wb_blkcg_offline(blkcg);

	/* put the base cgwb reference allowing step 2 to be triggered */
	blkcg_cgwb_put(blkcg);
}