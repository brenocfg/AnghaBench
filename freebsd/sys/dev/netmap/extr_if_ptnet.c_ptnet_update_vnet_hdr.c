#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ptnet_softc {int /*<<< orphan*/  vnet_hdr_len; TYPE_3__* ptna; int /*<<< orphan*/  iomem; } ;
struct TYPE_4__ {int /*<<< orphan*/  virt_hdr_len; } ;
struct TYPE_5__ {TYPE_1__ up; } ;
struct TYPE_6__ {TYPE_2__ hwup; } ;

/* Variables and functions */
 unsigned int PTNET_HDR_SIZE ; 
 int /*<<< orphan*/  PTNET_IO_VNET_HDR_LEN ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ptnet_vnet_hdr ; 

__attribute__((used)) static void
ptnet_update_vnet_hdr(struct ptnet_softc *sc)
{
	unsigned int wanted_hdr_len = ptnet_vnet_hdr ? PTNET_HDR_SIZE : 0;

	bus_write_4(sc->iomem, PTNET_IO_VNET_HDR_LEN, wanted_hdr_len);
	sc->vnet_hdr_len = bus_read_4(sc->iomem, PTNET_IO_VNET_HDR_LEN);
	sc->ptna->hwup.up.virt_hdr_len = sc->vnet_hdr_len;
}