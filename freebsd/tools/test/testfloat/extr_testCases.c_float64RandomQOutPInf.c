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
typedef  int /*<<< orphan*/  float64 ;

/* Variables and functions */
 int /*<<< orphan*/  SETFLOAT64 (int /*<<< orphan*/ ,int,int) ; 
 size_t float64NumQOut ; 
 int* float64QOut ; 
 int randomUint32 () ; 
 size_t randomUint8 () ; 

__attribute__((used)) static float64 float64RandomQOutPInf( void )
{
    float64 z;

    SETFLOAT64(
        z,
          float64QOut[ randomUint8() % float64NumQOut ]
        | ( randomUint32() & 0x000FFFFF ),
        randomUint32()
    );
    return z;

}