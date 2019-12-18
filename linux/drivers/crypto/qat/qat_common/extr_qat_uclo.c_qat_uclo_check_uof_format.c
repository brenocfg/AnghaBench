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
struct icp_qat_uof_filehdr {int maj_ver; int min_ver; scalar_t__ file_id; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ICP_QAT_UOF_FID ; 
 int ICP_QAT_UOF_MAJVER ; 
 int ICP_QAT_UOF_MINVER ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static int qat_uclo_check_uof_format(struct icp_qat_uof_filehdr *hdr)
{
	int maj = hdr->maj_ver & 0xff;
	int min = hdr->min_ver & 0xff;

	if (hdr->file_id != ICP_QAT_UOF_FID) {
		pr_err("QAT: Invalid header 0x%x\n", hdr->file_id);
		return -EINVAL;
	}
	if (min != ICP_QAT_UOF_MINVER || maj != ICP_QAT_UOF_MAJVER) {
		pr_err("QAT: bad UOF version, major 0x%x, minor 0x%x\n",
		       maj, min);
		return -EINVAL;
	}
	return 0;
}