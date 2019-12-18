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
struct bxe_fastpath {int /*<<< orphan*/ * sb_running_index; int /*<<< orphan*/  fp_hc_idx; } ;

/* Variables and functions */
 size_t SM_RX_ID ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void
bxe_update_fp_sb_idx(struct bxe_fastpath *fp)
{
    mb(); /* status block is written to by the chip */
    fp->fp_hc_idx = fp->sb_running_index[SM_RX_ID];
}