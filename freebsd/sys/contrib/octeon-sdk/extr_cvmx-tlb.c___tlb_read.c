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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_EHB ; 
 int /*<<< orphan*/  CVMX_TLBR ; 

__attribute__((used)) static inline void __tlb_read(void){
    CVMX_EHB;
    CVMX_TLBR;
    CVMX_EHB;
}