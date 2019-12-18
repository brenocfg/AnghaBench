#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ipprt; } ;
struct TYPE_10__ {TYPE_3__ cn38xx; } ;
struct TYPE_7__ {int port; } ;
struct TYPE_8__ {TYPE_1__ s_cn68xx; } ;
struct TYPE_11__ {TYPE_4__ word1; TYPE_2__ word2; } ;
typedef  TYPE_5__ cvmx_wqe_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_FEATURE_CN68XX_WQE ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_wqe_set_port(cvmx_wqe_t *work, int port)
{
    if (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE))
	port = work->word2.s_cn68xx.port = port;
    else
	port = work->word1.cn38xx.ipprt = port;
}