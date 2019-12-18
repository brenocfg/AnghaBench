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
struct TYPE_4__ {scalar_t__ sign; scalar_t__ exp; int /*<<< orphan*/  sig; scalar_t__ isZero; scalar_t__ isInf; scalar_t__ isNaN; } ;
typedef  TYPE_1__ floatX ;
typedef  scalar_t__ flag ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ lt64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static flag floatXLt( floatX ax, floatX bx )
{

    if ( ax.isNaN || bx.isNaN ) return FALSE;
    if ( ax.isZero && bx.isZero ) return FALSE;
    if ( ax.sign != bx.sign ) return ax.sign;
    if ( ax.isInf && bx.isInf ) return FALSE;
    if ( ax.sign ) {
        if ( ax.isInf || bx.isZero ) return TRUE;
        if ( bx.isInf || ax.isZero ) return FALSE;
        if ( bx.exp < ax.exp ) return TRUE;
        if ( ax.exp < bx.exp ) return FALSE;
        return lt64( bx.sig, ax.sig );
    }
    else {
        if ( bx.isInf || ax.isZero ) return TRUE;
        if ( ax.isInf || bx.isZero ) return FALSE;
        if ( ax.exp < bx.exp ) return TRUE;
        if ( bx.exp < ax.exp ) return FALSE;
        return lt64( ax.sig, bx.sig );
    }

}