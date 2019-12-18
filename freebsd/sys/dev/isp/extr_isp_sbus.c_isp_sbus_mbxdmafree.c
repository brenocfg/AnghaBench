#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  reqdmat; int /*<<< orphan*/  reqmap; int /*<<< orphan*/  respdmat; int /*<<< orphan*/  respmap; TYPE_4__* pcmd_pool; int /*<<< orphan*/  dmat; } ;
struct TYPE_6__ {int isp_maxcmds; scalar_t__ isp_result_dma; scalar_t__ isp_rquest_dma; int /*<<< orphan*/ * isp_rquest; TYPE_1__ isp_osinfo; int /*<<< orphan*/ * isp_result; TYPE_4__* isp_xflist; } ;
typedef  TYPE_2__ ispsoftc_t ;
struct TYPE_7__ {int /*<<< orphan*/  dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isp_sbus_mbxdmafree(ispsoftc_t *isp)
{
	int i;

	if (isp->isp_xflist != NULL) {
		free(isp->isp_xflist, M_DEVBUF);
		isp->isp_xflist = NULL;
	}
	if (isp->isp_osinfo.pcmd_pool != NULL) {
		for (i = 0; i < isp->isp_maxcmds; i++) {
			bus_dmamap_destroy(isp->isp_osinfo.dmat,
			    isp->isp_osinfo.pcmd_pool[i].dmap);
		}
		free(isp->isp_osinfo.pcmd_pool, M_DEVBUF);
		isp->isp_osinfo.pcmd_pool = NULL;
	}
	if (isp->isp_result_dma != 0) {
		bus_dmamap_unload(isp->isp_osinfo.respdmat,
		    isp->isp_osinfo.respmap);
		isp->isp_result_dma = 0;
	}
	if (isp->isp_result != NULL) {
		bus_dmamem_free(isp->isp_osinfo.respdmat, isp->isp_result,
		    isp->isp_osinfo.respmap);
		bus_dma_tag_destroy(isp->isp_osinfo.respdmat);
		isp->isp_result = NULL;
	}
	if (isp->isp_rquest_dma != 0) {
		bus_dmamap_unload(isp->isp_osinfo.reqdmat,
		    isp->isp_osinfo.reqmap);
		isp->isp_rquest_dma = 0;
	}
	if (isp->isp_rquest != NULL) {
		bus_dmamem_free(isp->isp_osinfo.reqdmat, isp->isp_rquest,
		    isp->isp_osinfo.reqmap);
		bus_dma_tag_destroy(isp->isp_osinfo.reqdmat);
		isp->isp_rquest = NULL;
	}
}