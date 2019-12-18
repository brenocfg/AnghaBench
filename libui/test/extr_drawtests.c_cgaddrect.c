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
typedef  int /*<<< orphan*/  uiDrawPath ;
struct TYPE_3__ {double AreaHeight; } ;
typedef  TYPE_1__ uiAreaDrawParams ;

/* Variables and functions */
 int /*<<< orphan*/  uiDrawPathAddRectangle (int /*<<< orphan*/ *,double,double,double,double) ; 

__attribute__((used)) static void cgaddrect(uiDrawPath *path, uiAreaDrawParams *p, double x, double y, double width, double height)
{
	uiDrawPathAddRectangle(path,
		x, p->AreaHeight - y - height,
		width, height);
}