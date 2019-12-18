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
struct smb_vc {struct nbpcb* vc_tdata; } ;
struct nbpcb {int /*<<< orphan*/ * nbp_tso; } ;

/* Variables and functions */
 int /*<<< orphan*/  sorwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sowwakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
smb_nbst_intr(struct smb_vc *vcp)
{
	struct nbpcb *nbp = vcp->vc_tdata;

	if (nbp == NULL || nbp->nbp_tso == NULL)
		return;
	sorwakeup(nbp->nbp_tso);
	sowwakeup(nbp->nbp_tso);
}