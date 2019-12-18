#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct synps_platform_data {int /*<<< orphan*/  (* get_dtype ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_mtype ) (int /*<<< orphan*/ ) ;} ;
struct synps_edac_priv {int /*<<< orphan*/  baseaddr; struct synps_platform_data* p_data; } ;
struct mem_ctl_info {size_t nr_csrows; struct csrow_info** csrows; struct synps_edac_priv* pvt_info; } ;
struct dimm_info {size_t nr_pages; int /*<<< orphan*/  dtype; int /*<<< orphan*/  grain; int /*<<< orphan*/  mtype; int /*<<< orphan*/  edac_mode; } ;
struct csrow_info {int nr_channels; TYPE_1__** channels; } ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  SYNPS_EDAC_ERR_GRAIN ; 
 size_t get_memsize () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_csrows(struct mem_ctl_info *mci)
{
	struct synps_edac_priv *priv = mci->pvt_info;
	const struct synps_platform_data *p_data;
	struct csrow_info *csi;
	struct dimm_info *dimm;
	u32 size, row;
	int j;

	p_data = priv->p_data;

	for (row = 0; row < mci->nr_csrows; row++) {
		csi = mci->csrows[row];
		size = get_memsize();

		for (j = 0; j < csi->nr_channels; j++) {
			dimm		= csi->channels[j]->dimm;
			dimm->edac_mode	= EDAC_FLAG_SECDED;
			dimm->mtype	= p_data->get_mtype(priv->baseaddr);
			dimm->nr_pages	= (size >> PAGE_SHIFT) / csi->nr_channels;
			dimm->grain	= SYNPS_EDAC_ERR_GRAIN;
			dimm->dtype	= p_data->get_dtype(priv->baseaddr);
		}
	}
}