#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cSpeed; scalar_t__ cSize; } ;
typedef  TYPE_1__ BMK_benchResult_t ;

/* Variables and functions */
 int BETTER_RESULT ; 
 int SIZE_RESULT ; 
 int SPEED_RESULT ; 
 int WORSE_RESULT ; 

__attribute__((used)) static int
speedSizeCompare(const BMK_benchResult_t r1, const BMK_benchResult_t r2)
{
    if(r1.cSpeed < r2.cSpeed) {
        if(r1.cSize >= r2.cSize) {
            return BETTER_RESULT;
        }
        return SPEED_RESULT; /* r2 is smaller but not faster. */
    } else {
        if(r1.cSize <= r2.cSize) {
            return WORSE_RESULT;
        }
        return SIZE_RESULT; /* r2 is faster but not smaller */
    }
}