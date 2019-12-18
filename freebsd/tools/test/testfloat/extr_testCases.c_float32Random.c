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
typedef  int /*<<< orphan*/  float32 ;

/* Variables and functions */
 int /*<<< orphan*/  float32RandomQInfP3 () ; 
 int /*<<< orphan*/  float32RandomQInfPInf () ; 
 int /*<<< orphan*/  float32RandomQOutP3 () ; 
 int /*<<< orphan*/  float32RandomQOutPInf () ; 
 int randomUint8 () ; 

__attribute__((used)) static float32 float32Random( void )
{

    switch ( randomUint8() & 7 ) {
     case 0:
     case 1:
     case 2:
        return float32RandomQOutP3();
     case 3:
        return float32RandomQOutPInf();
     case 4:
     case 5:
     case 6:
        return float32RandomQInfP3();
     default:
        return float32RandomQInfPInf();
    }

}