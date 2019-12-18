#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int parent_tag; } ;
struct TYPE_6__ {TYPE_1__ flags; int /*<<< orphan*/  parent_tag; int /*<<< orphan*/  pci_dev; } ;
typedef  TYPE_2__ qlnx_host_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_2__*,char*) ; 
 int bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_alloc_parent_dma_tag(qlnx_host_t *ha)
{
        int             ret;
        device_t        dev;

        dev = ha->pci_dev;

        /*
         * Allocate parent DMA Tag
         */
        ret = bus_dma_tag_create(
                        bus_get_dma_tag(dev),   /* parent */
                        1,((bus_size_t)(1ULL << 32)),/* alignment, boundary */
                        BUS_SPACE_MAXADDR,      /* lowaddr */
                        BUS_SPACE_MAXADDR,      /* highaddr */
                        NULL, NULL,             /* filter, filterarg */
                        BUS_SPACE_MAXSIZE_32BIT,/* maxsize */
                        0,                      /* nsegments */
                        BUS_SPACE_MAXSIZE_32BIT,/* maxsegsize */
                        0,                      /* flags */
                        NULL, NULL,             /* lockfunc, lockarg */
                        &ha->parent_tag);

        if (ret) {
                QL_DPRINT1(ha, "could not create parent dma tag\n");
                return (-1);
        }

        ha->flags.parent_tag = 1;

        return (0);
}