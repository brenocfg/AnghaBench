#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {TYPE_1__* netEnvs; } ;
typedef  TYPE_2__ t_FmPcd ;
struct TYPE_3__ {size_t* lcvs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 

uint32_t FmPcdGetLcv(t_Handle h_FmPcd, uint32_t netEnvId, uint8_t hdrNum)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;

    ASSERT_COND(h_FmPcd);
    return p_FmPcd->netEnvs[netEnvId].lcvs[hdrNum];
}