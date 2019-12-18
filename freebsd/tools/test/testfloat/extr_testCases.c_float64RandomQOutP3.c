#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  size_t int8 ;
typedef  int /*<<< orphan*/  float64 ;
struct TYPE_2__ {scalar_t__ low; int high; } ;

/* Variables and functions */
 int /*<<< orphan*/  SETFLOAT64 (int /*<<< orphan*/ ,int,scalar_t__) ; 
 size_t float64NumP2 ; 
 size_t float64NumQOut ; 
 TYPE_1__* float64P2 ; 
 int* float64QOut ; 
 size_t randomUint8 () ; 

__attribute__((used)) static float64 float64RandomQOutP3( void )
{
    int8 sigNum1, sigNum2;
    uint32 sig1Low, sig2Low, zLow;
    float64 z;

    sigNum1 = randomUint8() % float64NumP2;
    sigNum2 = randomUint8() % float64NumP2;
    sig1Low = float64P2[ sigNum1 ].low;
    sig2Low = float64P2[ sigNum2 ].low;
    zLow = sig1Low + sig2Low;
    SETFLOAT64(
        z,
          float64QOut[ randomUint8() % float64NumQOut ]
        | (   (   float64P2[ sigNum1 ].high
                + float64P2[ sigNum2 ].high
                + ( zLow < sig1Low )
              )
            & 0x000FFFFF
          ),
        zLow
    );
    return z;

}