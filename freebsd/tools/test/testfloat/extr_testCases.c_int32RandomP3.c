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
typedef  int /*<<< orphan*/  sbits32 ;
typedef  int /*<<< orphan*/  int32 ;

/* Variables and functions */
 size_t int32NumP1 ; 
 scalar_t__* int32P1 ; 
 size_t randomUint8 () ; 

__attribute__((used)) static int32 int32RandomP3( void )
{

    return
        (sbits32) (
              int32P1[ randomUint8() % int32NumP1 ]
            + int32P1[ randomUint8() % int32NumP1 ]
            + int32P1[ randomUint8() % int32NumP1 ]
        );

}