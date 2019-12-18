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
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; struct ie31200_priv* pvt_info; } ;
struct ie31200_priv {int /*<<< orphan*/  c1errlog; int /*<<< orphan*/  c0errlog; } ;
struct ie31200_error_info {int errsts; int errsts2; void** eccerrlog; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE31200_ERRSTS ; 
 int IE31200_ERRSTS_BITS ; 
 int /*<<< orphan*/  ie31200_clear_error_info (struct mem_ctl_info*) ; 
 void* lo_hi_readq (int /*<<< orphan*/ ) ; 
 int nr_channels ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ie31200_get_and_clear_error_info(struct mem_ctl_info *mci,
					     struct ie31200_error_info *info)
{
	struct pci_dev *pdev;
	struct ie31200_priv *priv = mci->pvt_info;

	pdev = to_pci_dev(mci->pdev);

	/*
	 * This is a mess because there is no atomic way to read all the
	 * registers at once and the registers can transition from CE being
	 * overwritten by UE.
	 */
	pci_read_config_word(pdev, IE31200_ERRSTS, &info->errsts);
	if (!(info->errsts & IE31200_ERRSTS_BITS))
		return;

	info->eccerrlog[0] = lo_hi_readq(priv->c0errlog);
	if (nr_channels == 2)
		info->eccerrlog[1] = lo_hi_readq(priv->c1errlog);

	pci_read_config_word(pdev, IE31200_ERRSTS, &info->errsts2);

	/*
	 * If the error is the same for both reads then the first set
	 * of reads is valid.  If there is a change then there is a CE
	 * with no info and the second set of reads is valid and
	 * should be UE info.
	 */
	if ((info->errsts ^ info->errsts2) & IE31200_ERRSTS_BITS) {
		info->eccerrlog[0] = lo_hi_readq(priv->c0errlog);
		if (nr_channels == 2)
			info->eccerrlog[1] =
				lo_hi_readq(priv->c1errlog);
	}

	ie31200_clear_error_info(mci);
}