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
struct TYPE_3__ {size_t term1Num; int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ sequenceT ;
typedef  int /*<<< orphan*/  sbits32 ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 size_t int32NumP1 ; 
 int /*<<< orphan*/ * int32P1 ; 

__attribute__((used)) static int32 int32NextP1( sequenceT *sequencePtr )
{
    uint8 termNum;
    int32 z;

    termNum = sequencePtr->term1Num;
    z = int32P1[ termNum ];
    ++termNum;
    if ( int32NumP1 <= termNum ) {
        termNum = 0;
        sequencePtr->done = TRUE;
    }
    sequencePtr->term1Num = termNum;
    return (sbits32) z;

}