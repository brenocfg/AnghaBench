#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tx_tag; } ;
typedef  TYPE_1__ qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  QLNX_MAX_SEGMENTS ; 
 int /*<<< orphan*/  QLNX_MAX_TSO_FRAME_SIZE ; 
 int /*<<< orphan*/  QLNX_MAX_TX_MBUF_SIZE ; 
 int /*<<< orphan*/  QL_DPRINT1 (TYPE_1__*,char*) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlnx_alloc_tx_dma_tag(qlnx_host_t *ha)
{
        if (bus_dma_tag_create(NULL,    /* parent */
                1, 0,    /* alignment, bounds */
                BUS_SPACE_MAXADDR,       /* lowaddr */
                BUS_SPACE_MAXADDR,       /* highaddr */
                NULL, NULL,      /* filter, filterarg */
                QLNX_MAX_TSO_FRAME_SIZE,     /* maxsize */
                QLNX_MAX_SEGMENTS,        /* nsegments */
                QLNX_MAX_TX_MBUF_SIZE,	  /* maxsegsize */
                0,        /* flags */
                NULL,    /* lockfunc */
                NULL,    /* lockfuncarg */
                &ha->tx_tag)) {

                QL_DPRINT1(ha, "tx_tag alloc failed\n");
                return (-1);
        }

	return (0);
}