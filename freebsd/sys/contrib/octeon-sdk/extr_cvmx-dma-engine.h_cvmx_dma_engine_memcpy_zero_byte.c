#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dici_mode; } ;
struct TYPE_8__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_3__ cvmx_dpi_dma_control_t ;
struct TYPE_7__ {int addr; scalar_t__ wqp; int /*<<< orphan*/  type; } ;
struct TYPE_9__ {TYPE_2__ s; scalar_t__ u64; } ;
typedef  TYPE_4__ cvmx_dma_engine_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_DMA_ENGINE_TRANSFER_INTERNAL ; 
 int /*<<< orphan*/  CVMX_DPI_DMA_CONTROL ; 
 int /*<<< orphan*/  OCTEON_FEATURE_DICI_MODE ; 
 int cvmx_dma_engine_transfer (int,TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvmx_ptr_to_phys (void*) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_dma_engine_memcpy_zero_byte(int engine, void *dest, void *source, int length, int core)
{
    cvmx_dma_engine_header_t header;
    header.u64 = 0;
    header.s.type = CVMX_DMA_ENGINE_TRANSFER_INTERNAL;
    /* If dici_mode is set, DPI increments the DPI_DMA_PPn_CNT[CNT], where the
       value of core n is PTR<5:0>-1 when WQP=0 and PTR != 0 && PTR < 64. */
    if (octeon_has_feature(OCTEON_FEATURE_DICI_MODE))
    {
        cvmx_dpi_dma_control_t dma_control;
        dma_control.u64 = cvmx_read_csr(CVMX_DPI_DMA_CONTROL);
        if (dma_control.s.dici_mode)
        {
           header.s.wqp = 0;           // local memory pointer
           header.s.addr = core + 1;
        }
    }
    return cvmx_dma_engine_transfer(engine, header, cvmx_ptr_to_phys(source),
                                    cvmx_ptr_to_phys(dest), length);
}