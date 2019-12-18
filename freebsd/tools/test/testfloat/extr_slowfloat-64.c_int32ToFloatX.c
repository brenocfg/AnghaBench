#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32 ;
struct TYPE_4__ {int a0; scalar_t__ a1; } ;
struct TYPE_5__ {int sign; int exp; TYPE_1__ sig; void* isZero; void* isInf; void* isNaN; } ;
typedef  TYPE_2__ floatX ;
typedef  int bits64 ;

/* Variables and functions */
 void* FALSE ; 
 int LIT64 (int) ; 
 void* TRUE ; 

__attribute__((used)) static floatX int32ToFloatX( int32 a )
{
    floatX ax;

    ax.isNaN = FALSE;
    ax.isInf = FALSE;
    ax.sign = ( a < 0 );
    ax.sig.a1 = 0;
    ax.sig.a0 = ax.sign ? - (bits64) a : a;
    if ( a == 0 ) {
        ax.isZero = TRUE;
        return ax;
    }
    ax.isZero = FALSE;
    ax.sig.a0 <<= 24;
    ax.exp = 31;
    while ( ax.sig.a0 < LIT64( 0x0080000000000000 ) ) {
        ax.sig.a0 <<= 1;
        --ax.exp;
    }
    return ax;

}