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
typedef  size_t varInds_t ;
struct TYPE_3__ {scalar_t__* vals; } ;
typedef  TYPE_1__ paramValues_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 size_t NUM_PARAMS ; 

__attribute__((used)) static void display_params_tested(paramValues_t cParams)
{
    varInds_t vi;
    DISPLAYLEVEL(3, "\r testing :");
    for (vi=0; vi < NUM_PARAMS; vi++) {
        DISPLAYLEVEL(3, "%3u,", (unsigned)cParams.vals[vi]);
    }
    DISPLAYLEVEL(3, "\b    \r");
}