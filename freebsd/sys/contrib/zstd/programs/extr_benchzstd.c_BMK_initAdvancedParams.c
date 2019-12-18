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
struct TYPE_3__ {int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ const BMK_advancedParams_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMK_TIMETEST_DEFAULT_S ; 
 int /*<<< orphan*/  BMK_both ; 
 int /*<<< orphan*/  ZSTD_lcm_auto ; 

BMK_advancedParams_t BMK_initAdvancedParams(void) {
    BMK_advancedParams_t const res = {
        BMK_both, /* mode */
        BMK_TIMETEST_DEFAULT_S, /* nbSeconds */
        0, /* blockSize */
        0, /* nbWorkers */
        0, /* realTime */
        0, /* additionalParam */
        0, /* ldmFlag */
        0, /* ldmMinMatch */
        0, /* ldmHashLog */
        0, /* ldmBuckSizeLog */
        0,  /* ldmHashRateLog */
        ZSTD_lcm_auto /* literalCompressionMode */
    };
    return res;
}