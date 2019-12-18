#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t u_int ;
struct sec_softc {int dummy; } ;
struct sec_hw_desc_ptr {int shdp_j; int /*<<< orphan*/  shdp_ptr; scalar_t__ shdp_extent; scalar_t__ shdp_length; } ;
struct sec_desc_map_info {TYPE_4__* sdmi_lt_first; scalar_t__ sdmi_lt_used; TYPE_2__* sdmi_lt_last; scalar_t__ sdmi_offset; int /*<<< orphan*/  member_5; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; scalar_t__ member_2; scalar_t__ member_1; struct sec_softc* member_0; } ;
struct sec_desc {TYPE_3__* sd_desc; int /*<<< orphan*/  sd_lt_used; int /*<<< orphan*/ * sd_ptr_dmem; } ;
typedef  scalar_t__ data ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_8__ {int /*<<< orphan*/  sl_lt_paddr; } ;
struct TYPE_7__ {struct sec_hw_desc_ptr* shd_pointer; } ;
struct TYPE_6__ {TYPE_1__* sl_lt; } ;
struct TYPE_5__ {int shl_r; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_LOCK_ASSERT (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int SEC_MEMORY ; 
 int /*<<< orphan*/  descriptors ; 
 int sec_desc_map_dma (struct sec_softc*,int /*<<< orphan*/ *,void*,scalar_t__,int,struct sec_desc_map_info*) ; 

__attribute__((used)) static int
sec_make_pointer(struct sec_softc *sc, struct sec_desc *desc,
    u_int n, void *data, bus_size_t doffset, bus_size_t dsize, int dtype)
{
	struct sec_desc_map_info sdmi = { sc, dsize, doffset, NULL, NULL, 0 };
	struct sec_hw_desc_ptr *ptr;
	int error;

	SEC_LOCK_ASSERT(sc, descriptors);

	/* For flat memory map only requested region */
	if (dtype == SEC_MEMORY) {
		 data = (uint8_t*)(data) + doffset;
		 sdmi.sdmi_offset = 0;
	}

	error = sec_desc_map_dma(sc, &(desc->sd_ptr_dmem[n]), data, dsize,
	    dtype, &sdmi);

	if (error)
		return (error);

	sdmi.sdmi_lt_last->sl_lt->shl_r = 1;
	desc->sd_lt_used += sdmi.sdmi_lt_used;

	ptr = &(desc->sd_desc->shd_pointer[n]);
	ptr->shdp_length = dsize;
	ptr->shdp_extent = 0;
	ptr->shdp_j = 1;
	ptr->shdp_ptr = sdmi.sdmi_lt_first->sl_lt_paddr;

	return (0);
}