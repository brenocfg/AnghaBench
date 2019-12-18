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
typedef  int uintmax_t ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxfw_mfa2_tlv_multi {int dummy; } ;
struct mlxfw_mfa2_tlv_component_descriptor {int /*<<< orphan*/  size; int /*<<< orphan*/  cb_offset_l; int /*<<< orphan*/  cb_offset_h; int /*<<< orphan*/  identifier; } ;
struct mlxfw_mfa2_tlv {int dummy; } ;
struct mlxfw_mfa2_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlxfw_mfa2_tlv_component_descriptor* mlxfw_mfa2_tlv_component_descriptor_get (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv const*) ; 
 struct mlxfw_mfa2_tlv* mlxfw_mfa2_tlv_multi_child (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv_multi const*) ; 
 struct mlxfw_mfa2_tlv_multi* mlxfw_mfa2_tlv_multi_get (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv const*) ; 
 int /*<<< orphan*/  mlxfw_mfa2_tlv_multi_validate (struct mlxfw_mfa2_file const*,struct mlxfw_mfa2_tlv_multi const*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
mlxfw_mfa2_file_comp_validate(const struct mlxfw_mfa2_file *mfa2_file,
			      const struct mlxfw_mfa2_tlv *comp_tlv,
			      u16 comp_idx)
{
	const struct mlxfw_mfa2_tlv_component_descriptor *cdesc;
	const struct mlxfw_mfa2_tlv_multi *multi;
	const struct mlxfw_mfa2_tlv *tlv;

	pr_debug("Component %d\n", comp_idx);

	multi = mlxfw_mfa2_tlv_multi_get(mfa2_file, comp_tlv);
	if (!multi) {
		pr_err("Component %d is not a valid TLV error\n", comp_idx);
		return false;
	}

	if (!mlxfw_mfa2_tlv_multi_validate(mfa2_file, multi))
		return false;

	/* Check that component have COMPONENT_DESCRIPTOR as first child */
	tlv = mlxfw_mfa2_tlv_multi_child(mfa2_file, multi);
	if (!tlv) {
		pr_err("Component descriptor %d multi TLV error\n", comp_idx);
		return false;
	}

	cdesc = mlxfw_mfa2_tlv_component_descriptor_get(mfa2_file, tlv);
	if (!cdesc) {
		pr_err("Component %d does not have a valid descriptor\n",
		       comp_idx);
		return false;
	}
	pr_debug("  -- Component type %d\n", be16_to_cpu(cdesc->identifier));
	pr_debug("  -- Offset %#jx and size %d\n",
		 (uintmax_t)((u64) be32_to_cpu(cdesc->cb_offset_h) << 32)
		 | be32_to_cpu(cdesc->cb_offset_l), be32_to_cpu(cdesc->size));

	return true;
}