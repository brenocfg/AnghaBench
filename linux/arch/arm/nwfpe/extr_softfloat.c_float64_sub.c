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
typedef  int /*<<< orphan*/  float64 ;
typedef  scalar_t__ flag ;

/* Variables and functions */
 int /*<<< orphan*/  addFloat64Sigs (struct roundingData*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ extractFloat64Sign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subFloat64Sigs (struct roundingData*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

float64 float64_sub( struct roundingData *roundData, float64 a, float64 b )
{
    flag aSign, bSign;

    aSign = extractFloat64Sign( a );
    bSign = extractFloat64Sign( b );
    if ( aSign == bSign ) {
        return subFloat64Sigs( roundData, a, b, aSign );
    }
    else {
        return addFloat64Sigs( roundData, a, b, aSign );
    }

}