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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int init_flags; } ;
typedef  TYPE_1__ cvmx_usb_internal_state_t ;

/* Variables and functions */
 int CVMX_USB_INITIALIZE_FLAGS_DEBUG_CSRS ; 
 int /*<<< orphan*/  cvmx_csr_db_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int /*<<< orphan*/  cvmx_get_proc_id () ; 
 int /*<<< orphan*/  cvmx_read64_uint64 (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_unlikely (int) ; 

__attribute__((used)) static inline uint64_t __cvmx_usb_read_csr64(cvmx_usb_internal_state_t *usb,
                                             uint64_t address)
{
    uint64_t result = cvmx_read64_uint64(address);
#if ALLOW_CSR_DECODES
    if (cvmx_unlikely(usb->init_flags & CVMX_USB_INITIALIZE_FLAGS_DEBUG_CSRS))
    {
        cvmx_dprintf("Read: ");
        cvmx_csr_db_decode(cvmx_get_proc_id(), address, result);
    }
#endif
    return result;
}