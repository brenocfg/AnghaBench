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
typedef  int /*<<< orphan*/  u32 ;
struct scmi_handle {int /*<<< orphan*/  dev; } ;
struct scmi_fc_info {int /*<<< orphan*/  limit_get_addr; int /*<<< orphan*/  limit_set_db; int /*<<< orphan*/  limit_set_addr; int /*<<< orphan*/  level_get_addr; int /*<<< orphan*/  level_set_db; int /*<<< orphan*/  level_set_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PERF_LEVEL_GET ; 
 int /*<<< orphan*/  PERF_LEVEL_SET ; 
 int /*<<< orphan*/  PERF_LIMITS_GET ; 
 int /*<<< orphan*/  PERF_LIMITS_SET ; 
 struct scmi_fc_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmi_perf_domain_desc_fc (struct scmi_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scmi_perf_domain_init_fc(const struct scmi_handle *handle,
				     u32 domain, struct scmi_fc_info **p_fc)
{
	struct scmi_fc_info *fc;

	fc = devm_kzalloc(handle->dev, sizeof(*fc), GFP_KERNEL);
	if (!fc)
		return;

	scmi_perf_domain_desc_fc(handle, domain, PERF_LEVEL_SET,
				 &fc->level_set_addr, &fc->level_set_db);
	scmi_perf_domain_desc_fc(handle, domain, PERF_LEVEL_GET,
				 &fc->level_get_addr, NULL);
	scmi_perf_domain_desc_fc(handle, domain, PERF_LIMITS_SET,
				 &fc->limit_set_addr, &fc->limit_set_db);
	scmi_perf_domain_desc_fc(handle, domain, PERF_LIMITS_GET,
				 &fc->limit_get_addr, NULL);
	*p_fc = fc;
}