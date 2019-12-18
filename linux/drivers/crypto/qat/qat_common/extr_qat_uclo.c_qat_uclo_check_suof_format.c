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
struct icp_qat_suof_filehdr {int maj_ver; int min_ver; scalar_t__ file_id; scalar_t__ fw_type; int num_chunks; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ICP_QAT_SUOF_FID ; 
 int ICP_QAT_SUOF_MAJVER ; 
 int ICP_QAT_SUOF_MINVER ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int qat_uclo_check_suof_format(struct icp_qat_suof_filehdr *suof_hdr)
{
	int maj = suof_hdr->maj_ver & 0xff;
	int min = suof_hdr->min_ver & 0xff;

	if (suof_hdr->file_id != ICP_QAT_SUOF_FID) {
		pr_err("QAT: invalid header 0x%x\n", suof_hdr->file_id);
		return -EINVAL;
	}
	if (suof_hdr->fw_type != 0) {
		pr_err("QAT: unsupported firmware type\n");
		return -EINVAL;
	}
	if (suof_hdr->num_chunks <= 0x1) {
		pr_err("QAT: SUOF chunk amount is incorrect\n");
		return -EINVAL;
	}
	if (maj != ICP_QAT_SUOF_MAJVER || min != ICP_QAT_SUOF_MINVER) {
		pr_err("QAT: bad SUOF version, major 0x%x, minor 0x%x\n",
		       maj, min);
		return -EINVAL;
	}
	return 0;
}