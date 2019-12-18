#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ cvmx_usbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBNX_DMA0_INB_CHN0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_uint64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __cvmx_usbd_write_csr32(cvmx_usbd_state_t *usb, uint64_t address, uint32_t value)
{
    cvmx_write64_uint32(address ^ 4, value);
    cvmx_read64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
}