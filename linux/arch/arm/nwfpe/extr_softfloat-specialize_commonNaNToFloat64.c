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
typedef  int float64 ;
struct TYPE_3__ {int high; scalar_t__ sign; } ;
typedef  TYPE_1__ commonNaNT ;
typedef  int bits64 ;

/* Variables and functions */
 int LIT64 (int) ; 

__attribute__((used)) static float64 commonNaNToFloat64( commonNaNT a )
{

    return
          ( ( (bits64) a.sign )<<63 )
        | LIT64( 0x7FF8000000000000 )
        | ( a.high>>12 );

}