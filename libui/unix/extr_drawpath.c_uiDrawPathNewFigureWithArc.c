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
typedef  int /*<<< orphan*/  uiDrawPath ;
struct piece {double* d; int b; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  add (int /*<<< orphan*/ *,struct piece*) ; 
 int /*<<< orphan*/  newFigureArc ; 
 int uiPi ; 

void uiDrawPathNewFigureWithArc(uiDrawPath *p, double xCenter, double yCenter, double radius, double startAngle, double sweep, int negative)
{
	struct piece piece;

	if (sweep > 2 * uiPi)
		sweep = 2 * uiPi;
	piece.type = newFigureArc;
	piece.d[0] = xCenter;
	piece.d[1] = yCenter;
	piece.d[2] = radius;
	piece.d[3] = startAngle;
	piece.d[4] = sweep;
	piece.b = negative;
	add(p, &piece);
}