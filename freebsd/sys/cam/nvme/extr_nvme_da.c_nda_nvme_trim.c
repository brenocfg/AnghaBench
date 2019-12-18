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
typedef  int uint32_t ;
struct nvme_dsm_range {int dummy; } ;
struct nda_softc {int /*<<< orphan*/  nsid; } ;
struct ccb_nvmeio {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  cam_fill_nvmeio (struct ccb_nvmeio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int) ; 
 int nda_default_timeout ; 
 int /*<<< orphan*/  ndadone ; 
 int /*<<< orphan*/  nvme_ns_trim_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
nda_nvme_trim(struct nda_softc *softc, struct ccb_nvmeio *nvmeio,
    void *payload, uint32_t num_ranges)
{
	cam_fill_nvmeio(nvmeio,
	    0,			/* retries */
	    ndadone,		/* cbfcnp */
	    CAM_DIR_OUT,	/* flags */
	    payload,		/* data_ptr */
	    num_ranges * sizeof(struct nvme_dsm_range), /* dxfer_len */
	    nda_default_timeout * 1000); /* timeout 30s */
	nvme_ns_trim_cmd(&nvmeio->cmd, softc->nsid, num_ranges);
}