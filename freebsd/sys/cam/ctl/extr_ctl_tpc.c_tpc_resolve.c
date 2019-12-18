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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct tpc_list {int ncscd; int /*<<< orphan*/ * cscd; int /*<<< orphan*/  init_port; TYPE_2__* lun; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctl_softc; int /*<<< orphan*/  lun; TYPE_1__* be_lun; } ;
struct TYPE_3__ {int blocksize; int pblockexp; int pblockoff; } ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 int /*<<< orphan*/  tpcl_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*,int*) ; 

__attribute__((used)) static uint64_t
tpc_resolve(struct tpc_list *list, uint16_t idx, uint32_t *ss,
    uint32_t *pb, uint32_t *pbo)
{

	if (idx == 0xffff) {
		if (ss && list->lun->be_lun)
			*ss = list->lun->be_lun->blocksize;
		if (pb && list->lun->be_lun)
			*pb = list->lun->be_lun->blocksize <<
			    list->lun->be_lun->pblockexp;
		if (pbo && list->lun->be_lun)
			*pbo = list->lun->be_lun->blocksize *
			    list->lun->be_lun->pblockoff;
		return (list->lun->lun);
	}
	if (idx >= list->ncscd)
		return (UINT64_MAX);
	return (tpcl_resolve(list->lun->ctl_softc,
	    list->init_port, &list->cscd[idx], ss, pb, pbo));
}