#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct pci_dev {int dummy; } ;
struct mem_ctl_info {struct i5100_priv* pvt_info; } ;
struct i5100_priv {int tolm; TYPE_2__** dmir; void** amir; TYPE_1__* mir; struct pci_dev* ch1mm; struct pci_dev* ch0mm; } ;
struct TYPE_4__ {int limit; int /*<<< orphan*/ * rank; } ;
struct TYPE_3__ {int limit; void** way; } ;

/* Variables and functions */
 int /*<<< orphan*/  I5100_AMIR_0 ; 
 int /*<<< orphan*/  I5100_AMIR_1 ; 
 int I5100_CHANNELS ; 
 scalar_t__ I5100_DMIR ; 
 int I5100_MAX_RANKS_PER_DIMM ; 
 int /*<<< orphan*/  I5100_MIR0 ; 
 int /*<<< orphan*/  I5100_MIR1 ; 
 int /*<<< orphan*/  I5100_TOLM ; 
 scalar_t__ i5100_dmir_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i5100_dmir_rank (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i5100_init_mtr (struct mem_ctl_info*) ; 
 scalar_t__ i5100_mir_limit (void*) ; 
 void* i5100_mir_way0 (void*) ; 
 void* i5100_mir_way1 (void*) ; 
 scalar_t__ i5100_tolm_tolm (void*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static void i5100_init_interleaving(struct pci_dev *pdev,
				    struct mem_ctl_info *mci)
{
	u16 w;
	u32 dw;
	struct i5100_priv *priv = mci->pvt_info;
	struct pci_dev *mms[2] = { priv->ch0mm, priv->ch1mm };
	int i;

	pci_read_config_word(pdev, I5100_TOLM, &w);
	priv->tolm = (u64) i5100_tolm_tolm(w) * 256 * 1024 * 1024;

	pci_read_config_word(pdev, I5100_MIR0, &w);
	priv->mir[0].limit = (u64) i5100_mir_limit(w) << 28;
	priv->mir[0].way[1] = i5100_mir_way1(w);
	priv->mir[0].way[0] = i5100_mir_way0(w);

	pci_read_config_word(pdev, I5100_MIR1, &w);
	priv->mir[1].limit = (u64) i5100_mir_limit(w) << 28;
	priv->mir[1].way[1] = i5100_mir_way1(w);
	priv->mir[1].way[0] = i5100_mir_way0(w);

	pci_read_config_word(pdev, I5100_AMIR_0, &w);
	priv->amir[0] = w;
	pci_read_config_word(pdev, I5100_AMIR_1, &w);
	priv->amir[1] = w;

	for (i = 0; i < I5100_CHANNELS; i++) {
		int j;

		for (j = 0; j < 5; j++) {
			int k;

			pci_read_config_dword(mms[i], I5100_DMIR + j * 4, &dw);

			priv->dmir[i][j].limit =
				(u64) i5100_dmir_limit(dw) << 28;
			for (k = 0; k < I5100_MAX_RANKS_PER_DIMM; k++)
				priv->dmir[i][j].rank[k] =
					i5100_dmir_rank(dw, k);
		}
	}

	i5100_init_mtr(mci);
}