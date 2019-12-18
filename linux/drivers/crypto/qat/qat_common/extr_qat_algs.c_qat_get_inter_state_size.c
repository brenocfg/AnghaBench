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
typedef  enum icp_qat_hw_auth_algo { ____Placeholder_icp_qat_hw_auth_algo } icp_qat_hw_auth_algo ;

/* Variables and functions */
 int EFAULT ; 
#define  ICP_QAT_HW_AUTH_ALGO_SHA1 130 
#define  ICP_QAT_HW_AUTH_ALGO_SHA256 129 
#define  ICP_QAT_HW_AUTH_ALGO_SHA512 128 
 int ICP_QAT_HW_SHA1_STATE1_SZ ; 
 int ICP_QAT_HW_SHA256_STATE1_SZ ; 
 int ICP_QAT_HW_SHA512_STATE1_SZ ; 

__attribute__((used)) static int qat_get_inter_state_size(enum icp_qat_hw_auth_algo qat_hash_alg)
{
	switch (qat_hash_alg) {
	case ICP_QAT_HW_AUTH_ALGO_SHA1:
		return ICP_QAT_HW_SHA1_STATE1_SZ;
	case ICP_QAT_HW_AUTH_ALGO_SHA256:
		return ICP_QAT_HW_SHA256_STATE1_SZ;
	case ICP_QAT_HW_AUTH_ALGO_SHA512:
		return ICP_QAT_HW_SHA512_STATE1_SZ;
	default:
		return -EFAULT;
	};
	return -EFAULT;
}