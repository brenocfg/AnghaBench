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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_TLB_WIRED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t __tlb_wired_index() {
    uint32_t  tlbi;

    CVMX_MF_TLB_WIRED(tlbi);
    return tlbi;
}