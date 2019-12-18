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
struct TYPE_3__ {double X; double Y; } ;
typedef  TYPE_1__ uiAreaMouseEvent ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  label ; 
 int /*<<< orphan*/  sprintf (char*,char*,double,double) ; 
 int /*<<< orphan*/  uiCheckboxSetText (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
	char pos[128];

	// wonderful, vanilla snprintf() isn't in visual studio 2013 - http://blogs.msdn.com/b/vcblog/archive/2013/07/19/c99-library-support-in-visual-studio-2013.aspx
	// we can't use _snprintf() in the test suite because that's msvc-only, so oops. sprintf() it is.
	sprintf(pos, "X %g Y %g", e->X, e->Y);
	uiCheckboxSetText(label, pos);
}