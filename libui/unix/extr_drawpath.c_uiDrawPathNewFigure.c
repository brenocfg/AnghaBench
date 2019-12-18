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
 int /*<<< orphan*/  newFigure ; 

void uiDrawPathNewFigure(uiDrawPath *p, double x, double y)
{
	struct piece piece;

	piece.type = newFigure;
	piece.d[0] = x;
	piece.d[1] = y;
	add(p, &piece);
}