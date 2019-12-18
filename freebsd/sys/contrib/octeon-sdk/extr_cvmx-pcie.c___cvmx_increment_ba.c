#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ba; } ;
struct TYPE_5__ {int /*<<< orphan*/  ba; } ;
struct TYPE_7__ {TYPE_2__ cn63xx; TYPE_1__ cn68xx; } ;
typedef  TYPE_3__ cvmx_sli_mem_access_subidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __cvmx_increment_ba(cvmx_sli_mem_access_subidx_t *pmas)
{   
    if (OCTEON_IS_MODEL(OCTEON_CN68XX))
        pmas->cn68xx.ba++;
    else
        pmas->cn63xx.ba++;
}