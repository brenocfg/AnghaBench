#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pages_per_block; scalar_t__ blocks; } ;

/* Variables and functions */
 TYPE_1__* cvmx_nand_state ; 
 int cvmx_pop (scalar_t__) ; 

__attribute__((used)) static inline int __cvmx_nand_get_row_bits(int chip)
{
    return cvmx_pop(cvmx_nand_state[chip].blocks-1) + cvmx_pop(cvmx_nand_state[chip].pages_per_block-1);
}