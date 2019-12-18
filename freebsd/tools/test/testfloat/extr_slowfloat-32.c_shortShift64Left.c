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
struct TYPE_4__ {int a0; int a1; } ;
typedef  TYPE_1__ bits64X ;

/* Variables and functions */

__attribute__((used)) static bits64X shortShift64Left( bits64X a, int8 shiftCount )
{
    int8 negShiftCount;

    negShiftCount = ( - shiftCount & 31 );
    a.a0 = ( a.a0<<shiftCount ) | ( a.a1>>negShiftCount );
    a.a1 <<= shiftCount;
    return a;

}