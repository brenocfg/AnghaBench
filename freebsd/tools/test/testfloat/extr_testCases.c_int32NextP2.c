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
struct TYPE_3__ {size_t term2Num; size_t term1Num; int /*<<< orphan*/  done; } ;
typedef  TYPE_1__ sequenceT ;
typedef  scalar_t__ sbits32 ;
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 size_t int32NumP1 ; 
 scalar_t__* int32P1 ; 

__attribute__((used)) static int32 int32NextP2( sequenceT *sequencePtr )
{
    uint8 term1Num, term2Num;
    int32 z;

    term2Num = sequencePtr->term2Num;
    term1Num = sequencePtr->term1Num;
    z = int32P1[ term1Num ] + int32P1[ term2Num ];
    ++term2Num;
    if ( int32NumP1 <= term2Num ) {
        ++term1Num;
        if ( int32NumP1 <= term1Num ) {
            term1Num = 0;
            sequencePtr->done = TRUE;
        }
        term2Num = term1Num;
        sequencePtr->term1Num = term1Num;
    }
    sequencePtr->term2Num = term2Num;
    return (sbits32) z;

}