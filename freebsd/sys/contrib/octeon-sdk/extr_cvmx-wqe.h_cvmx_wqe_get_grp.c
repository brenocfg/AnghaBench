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
struct TYPE_7__ {int grp; } ;
struct TYPE_6__ {int grp; } ;
struct TYPE_8__ {TYPE_2__ cn38xx; TYPE_1__ cn68xx; } ;
struct TYPE_9__ {TYPE_3__ word1; } ;
typedef  TYPE_4__ cvmx_wqe_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_FEATURE_CN68XX_WQE ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_wqe_get_grp(cvmx_wqe_t *work)
{
    int grp;

    if (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
	grp = work->word1.cn68xx.grp;
    else
	grp = work->word1.cn38xx.grp;

    return grp;
}