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
struct kobject {int dummy; } ;
struct cppc_perf_fb_ctrs {int /*<<< orphan*/  delivered; int /*<<< orphan*/  reference; int /*<<< orphan*/  member_0; } ;
struct cpc_desc {int /*<<< orphan*/  cpu_id; } ;
struct attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int cppc_get_perf_ctrs (int /*<<< orphan*/ ,struct cppc_perf_fb_ctrs*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cpc_desc* to_cpc_desc (struct kobject*) ; 

__attribute__((used)) static ssize_t show_feedback_ctrs(struct kobject *kobj,
		struct attribute *attr, char *buf)
{
	struct cpc_desc *cpc_ptr = to_cpc_desc(kobj);
	struct cppc_perf_fb_ctrs fb_ctrs = {0};
	int ret;

	ret = cppc_get_perf_ctrs(cpc_ptr->cpu_id, &fb_ctrs);
	if (ret)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "ref:%llu del:%llu\n",
			fb_ctrs.reference, fb_ctrs.delivered);
}