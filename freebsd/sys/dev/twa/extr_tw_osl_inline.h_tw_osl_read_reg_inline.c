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
struct twa_softc {int /*<<< orphan*/  bus_handle; int /*<<< orphan*/  bus_tag; } ;
struct tw_cl_ctlr_handle {scalar_t__ osl_ctlr_ctxt; } ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  TW_UINT32 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 scalar_t__ bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline TW_UINT32
tw_osl_read_reg_inline(struct tw_cl_ctlr_handle *ctlr_handle,
	TW_INT32 offset, TW_INT32 size)
{
	bus_space_tag_t		bus_tag =
		((struct twa_softc *)(ctlr_handle->osl_ctlr_ctxt))->bus_tag;
	bus_space_handle_t	bus_handle =
		((struct twa_softc *)(ctlr_handle->osl_ctlr_ctxt))->bus_handle;

	if (size == 4)
		return((TW_UINT32)bus_space_read_4(bus_tag, bus_handle,
			offset));
	else if (size == 2)
		return((TW_UINT32)bus_space_read_2(bus_tag, bus_handle,
			offset));
	else
		return((TW_UINT32)bus_space_read_1(bus_tag, bus_handle,
			offset));
}