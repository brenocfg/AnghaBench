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
typedef  size_t uint8 ;
struct TYPE_3__ {size_t term1Num; size_t expNum; int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ sequenceT ;
typedef  int float32 ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 size_t float32NumP2 ; 
 size_t float32NumQIn ; 
 int* float32P2 ; 
 int* float32QIn ; 

__attribute__((used)) static float32 float32NextQInP2( sequenceT *sequencePtr )
{
    uint8 expNum, sigNum;
    float32 z;

    sigNum = sequencePtr->term1Num;
    expNum = sequencePtr->expNum;
    z = float32QIn[ expNum ] | float32P2[ sigNum ];
    ++sigNum;
    if ( float32NumP2 <= sigNum ) {
        sigNum = 0;
        ++expNum;
        if ( float32NumQIn <= expNum ) {
            expNum = 0;
            sequencePtr->done = TRUE;
        }
        sequencePtr->expNum = expNum;
    }
    sequencePtr->term1Num = sigNum;
    return z;

}