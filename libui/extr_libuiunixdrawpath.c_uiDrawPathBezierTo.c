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
struct piece {double* d; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  add (int /*<<< orphan*/ *,struct piece*) ; 
 int /*<<< orphan*/  bezierTo ; 

void uiDrawPathBezierTo(uiDrawPath *p, double c1x, double c1y, double c2x, double c2y, double endX, double endY)
{
	struct piece piece;

	piece.type = bezierTo;
	piece.d[0] = c1x;
	piece.d[1] = c1y;
	piece.d[2] = c2x;
	piece.d[3] = c2y;
	piece.d[4] = endX;
	piece.d[5] = endY;
	add(p, &piece);
}