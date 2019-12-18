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
typedef  int u8 ;
typedef  int u16 ;
struct ecore_iwarp_fpdu {int fpdu_length; int mpa_frag_len; int /*<<< orphan*/  incomplete_bytes; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int ECORE_IWARP_FPDU_LEN_WITH_PAD (int) ; 
 int /*<<< orphan*/  ECORE_IWARP_INVALID_FPDU_LENGTH ; 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 

__attribute__((used)) static void
ecore_iwarp_update_fpdu_length(struct ecore_hwfn *p_hwfn,
			       struct ecore_iwarp_fpdu *fpdu,
			       u8 *mpa_data)
{
	u16 mpa_len;

	/* Update incomplete packets if needed */
	if (fpdu->incomplete_bytes == ECORE_IWARP_INVALID_FPDU_LENGTH) {
		mpa_len = fpdu->fpdu_length | *mpa_data;
		fpdu->fpdu_length = ECORE_IWARP_FPDU_LEN_WITH_PAD(mpa_len);
		fpdu->mpa_frag_len = fpdu->fpdu_length;
		/* one byte of hdr */
		fpdu->incomplete_bytes = fpdu->fpdu_length - 1;
		DP_VERBOSE(p_hwfn,
			   ECORE_MSG_RDMA,
			   "MPA_ALIGN: Partial header mpa_len=%x fpdu_length=%x incomplete_bytes=%x\n",
			   mpa_len, fpdu->fpdu_length, fpdu->incomplete_bytes);
	}
}