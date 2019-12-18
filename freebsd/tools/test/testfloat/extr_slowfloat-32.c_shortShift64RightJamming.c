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
typedef  int int8 ;
struct TYPE_4__ {int a1; int a0; } ;
typedef  TYPE_1__ bits64X ;
typedef  int bits32 ;

/* Variables and functions */

__attribute__((used)) static bits64X shortShift64RightJamming( bits64X a, int8 shiftCount )
{
    int8 negShiftCount;
    bits32 extra;

    negShiftCount = ( - shiftCount & 31 );
    extra = a.a1<<negShiftCount;
    a.a1 = ( a.a0<<negShiftCount ) | ( a.a1>>shiftCount ) | ( extra != 0 );
    a.a0 >>= shiftCount;
    return a;

}