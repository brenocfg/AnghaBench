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
typedef  int float32 ;

/* Variables and functions */
 size_t float32NumQOut ; 
 int* float32QOut ; 
 int randomUint32 () ; 
 size_t randomUint8 () ; 

__attribute__((used)) static float32 float32RandomQOutPInf( void )
{

    return
          float32QOut[ randomUint8() % float32NumQOut ]
        | ( randomUint32() & 0x007FFFFF );

}