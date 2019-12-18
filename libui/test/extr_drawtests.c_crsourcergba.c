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
struct TYPE_3__ {double R; double G; double B; double A; int /*<<< orphan*/  Type; } ;
typedef  TYPE_1__ uiDrawBrush ;

/* Variables and functions */
 int /*<<< orphan*/  uiDrawBrushTypeSolid ; 

__attribute__((used)) static void crsourcergba(uiDrawBrush *brush, double r, double g, double b, double a)
{
	brush->Type = uiDrawBrushTypeSolid;
	brush->R = r;
	brush->G = g;
	brush->B = b;
	brush->A = a;
}