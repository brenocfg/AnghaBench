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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {double A; int /*<<< orphan*/  B; int /*<<< orphan*/  G; int /*<<< orphan*/  R; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ uiDrawBrush ;

/* Variables and functions */
 int /*<<< orphan*/  d2dColorToRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 

__attribute__((used)) static void d2dSolidBrush(uiDrawBrush *brush, uint32_t color, double alpha)
{
	brush->Type = uiDrawBrushTypeSolid;
	d2dColorToRGB(color, &(brush->R), &(brush->G), &(brush->B));
	brush->A = alpha;
}