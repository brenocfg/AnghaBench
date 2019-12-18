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
struct TYPE_3__ {int /*<<< orphan*/ * vals; } ;
typedef  TYPE_1__ paramValues_t ;

/* Variables and functions */
 scalar_t__ invRangeMap (size_t,int /*<<< orphan*/ ) ; 
 unsigned int* rangetable ; 
 size_t strt_ind ; 

__attribute__((used)) static unsigned memoTableIndDirect(const paramValues_t* ptr, const varInds_t* varyParams, const size_t varyLen) {
    size_t i;
    unsigned ind = 0;
    for(i = 0; i < varyLen; i++) {
        varInds_t v = varyParams[i];
        if(v == strt_ind) continue; /* exclude strategy from memotable */
        ind *= rangetable[v]; ind += (unsigned)invRangeMap(v, ptr->vals[v]);
    }
    return ind;
}