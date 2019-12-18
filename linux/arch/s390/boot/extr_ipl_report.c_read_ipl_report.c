#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ipl_rl_hdr {int len; } ;
struct ipl_rb_hdr {int len; int rbt; } ;
struct ipl_rb_components {int dummy; } ;
struct ipl_rb_certificates {int dummy; } ;
struct ipl_pl_hdr {unsigned long len; } ;
struct TYPE_6__ {scalar_t__ ipl_parmblock_ptr; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int IPL_PL_FLAG_IPLSR ; 
 int IPL_PL_FLAG_SIPL ; 
#define  IPL_RBT_CERTIFICATES 129 
#define  IPL_RBT_COMPONENTS 128 
 TYPE_3__ S390_lowcore ; 
 int /*<<< orphan*/  copy_certificates_bootdata (struct ipl_rb_certificates*) ; 
 int /*<<< orphan*/  copy_components_bootdata (struct ipl_rb_components*) ; 
 unsigned long find_bootdata_space (struct ipl_rb_components*,struct ipl_rb_certificates*,unsigned long) ; 
 TYPE_2__ ipl_block ; 
 int /*<<< orphan*/  ipl_block_valid ; 
 int ipl_secure_flag ; 

unsigned long read_ipl_report(unsigned long safe_addr)
{
	struct ipl_rb_certificates *certs;
	struct ipl_rb_components *comps;
	struct ipl_pl_hdr *pl_hdr;
	struct ipl_rl_hdr *rl_hdr;
	struct ipl_rb_hdr *rb_hdr;
	unsigned long tmp;
	void *rl_end;

	/*
	 * Check if there is a IPL report by looking at the copy
	 * of the IPL parameter information block.
	 */
	if (!ipl_block_valid ||
	    !(ipl_block.hdr.flags & IPL_PL_FLAG_IPLSR))
		return safe_addr;
	ipl_secure_flag = !!(ipl_block.hdr.flags & IPL_PL_FLAG_SIPL);
	/*
	 * There is an IPL report, to find it load the pointer to the
	 * IPL parameter information block from lowcore and skip past
	 * the IPL parameter list, then align the address to a double
	 * word boundary.
	 */
	tmp = (unsigned long) S390_lowcore.ipl_parmblock_ptr;
	pl_hdr = (struct ipl_pl_hdr *) tmp;
	tmp = (tmp + pl_hdr->len + 7) & -8UL;
	rl_hdr = (struct ipl_rl_hdr *) tmp;
	/* Walk through the IPL report blocks in the IPL Report list */
	certs = NULL;
	comps = NULL;
	rl_end = (void *) rl_hdr + rl_hdr->len;
	rb_hdr = (void *) rl_hdr + sizeof(*rl_hdr);
	while ((void *) rb_hdr + sizeof(*rb_hdr) < rl_end &&
	       (void *) rb_hdr + rb_hdr->len <= rl_end) {

		switch (rb_hdr->rbt) {
		case IPL_RBT_CERTIFICATES:
			certs = (struct ipl_rb_certificates *) rb_hdr;
			break;
		case IPL_RBT_COMPONENTS:
			comps = (struct ipl_rb_components *) rb_hdr;
			break;
		default:
			break;
		}

		rb_hdr = (void *) rb_hdr + rb_hdr->len;
	}

	/*
	 * With either the component list or the certificate list
	 * missing the kernel will stay ignorant of secure IPL.
	 */
	if (!comps || !certs)
		return safe_addr;

	/*
	 * Copy component and certificate list to a safe area
	 * where the decompressed kernel can find them.
	 */
	safe_addr = find_bootdata_space(comps, certs, safe_addr);
	copy_components_bootdata(comps);
	copy_certificates_bootdata(certs);

	return safe_addr;
}