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
struct TYPE_4__ {scalar_t__ sign; scalar_t__ exp; int /*<<< orphan*/  sig; scalar_t__ isInf; scalar_t__ isZero; scalar_t__ isNaN; } ;
typedef  TYPE_1__ floatX ;
typedef  int flag ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ eq64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static flag floatXEq( floatX ax, floatX bx )
{

    if ( ax.isNaN || bx.isNaN ) return FALSE;
    if ( ax.isZero && bx.isZero ) return TRUE;
    if ( ax.sign != bx.sign ) return FALSE;
    if ( ax.isInf || bx.isInf ) return ax.isInf && bx.isInf;
    return ( ax.exp == bx.exp ) && eq64( ax.sig, bx.sig );

}