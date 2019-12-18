#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct roundingData {int dummy; } ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  float32 ;
typedef  int flag ;

/* Variables and functions */
 int /*<<< orphan*/  normalizeRoundAndPackFloat32 (struct roundingData*,int,int,int) ; 
 int /*<<< orphan*/  packFloat32 (int,int,int /*<<< orphan*/ ) ; 

float32 int32_to_float32(struct roundingData *roundData, int32 a)
{
    flag zSign;

    if ( a == 0 ) return 0;
    if ( a == 0x80000000 ) return packFloat32( 1, 0x9E, 0 );
    zSign = ( a < 0 );
    return normalizeRoundAndPackFloat32( roundData, zSign, 0x9C, zSign ? - a : a );

}