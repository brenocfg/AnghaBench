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
typedef  int /*<<< orphan*/  u8 ;
struct mlxfw_mfa2_tlv {int dummy; } ;
struct mlxfw_mfa2_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxfw_mfa2_valid_ptr (struct mlxfw_mfa2_file const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline const struct mlxfw_mfa2_tlv *
mlxfw_mfa2_tlv_get(const struct mlxfw_mfa2_file *mfa2_file, const u8 *ptr)
{
	if (!mlxfw_mfa2_valid_ptr(mfa2_file, ptr) ||
	    !mlxfw_mfa2_valid_ptr(mfa2_file, ptr + sizeof(struct mlxfw_mfa2_tlv)))
		return NULL;
	return (const struct mlxfw_mfa2_tlv *) ptr;
}