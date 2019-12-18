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
struct device_node {int dummy; } ;
typedef  enum l1d_flush_type { ____Placeholder_l1d_flush_type } l1d_flush_type ;

/* Variables and functions */
 int L1D_FLUSH_FALLBACK ; 
 int L1D_FLUSH_MTTRIG ; 
 int L1D_FLUSH_ORI ; 
 int /*<<< orphan*/  SEC_FTR_FAVOUR_SECURITY ; 
 int /*<<< orphan*/  SEC_FTR_L1D_FLUSH_HV ; 
 int /*<<< orphan*/  SEC_FTR_L1D_FLUSH_ORI30 ; 
 int /*<<< orphan*/  SEC_FTR_L1D_FLUSH_PR ; 
 int /*<<< orphan*/  SEC_FTR_L1D_FLUSH_TRIG2 ; 
 int /*<<< orphan*/  init_fw_feat_flags (struct device_node*) ; 
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ security_ftr_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_count_cache_flush () ; 
 int /*<<< orphan*/  setup_rfi_flush (int,int) ; 

__attribute__((used)) static void pnv_setup_rfi_flush(void)
{
	struct device_node *np, *fw_features;
	enum l1d_flush_type type;
	bool enable;

	/* Default to fallback in case fw-features are not available */
	type = L1D_FLUSH_FALLBACK;

	np = of_find_node_by_name(NULL, "ibm,opal");
	fw_features = of_get_child_by_name(np, "fw-features");
	of_node_put(np);

	if (fw_features) {
		init_fw_feat_flags(fw_features);
		of_node_put(fw_features);

		if (security_ftr_enabled(SEC_FTR_L1D_FLUSH_TRIG2))
			type = L1D_FLUSH_MTTRIG;

		if (security_ftr_enabled(SEC_FTR_L1D_FLUSH_ORI30))
			type = L1D_FLUSH_ORI;
	}

	enable = security_ftr_enabled(SEC_FTR_FAVOUR_SECURITY) && \
		 (security_ftr_enabled(SEC_FTR_L1D_FLUSH_PR)   || \
		  security_ftr_enabled(SEC_FTR_L1D_FLUSH_HV));

	setup_rfi_flush(type, enable);
	setup_count_cache_flush();
}