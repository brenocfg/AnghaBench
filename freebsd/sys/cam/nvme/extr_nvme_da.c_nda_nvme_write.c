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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nda_softc {int /*<<< orphan*/  nsid; } ;
struct ccb_nvmeio {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  cam_fill_nvmeio (struct ccb_nvmeio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int nda_default_timeout ; 
 int /*<<< orphan*/  ndadone ; 
 int /*<<< orphan*/  nvme_ns_write_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nda_nvme_write(struct nda_softc *softc, struct ccb_nvmeio *nvmeio,
    void *payload, uint64_t lba, uint32_t len, uint32_t count)
{
	cam_fill_nvmeio(nvmeio,
	    0,			/* retries */
	    ndadone,		/* cbfcnp */
	    CAM_DIR_OUT,	/* flags */
	    payload,		/* data_ptr */
	    len,		/* dxfer_len */
	    nda_default_timeout * 1000); /* timeout 30s */
	nvme_ns_write_cmd(&nvmeio->cmd, softc->nsid, lba, count);
}