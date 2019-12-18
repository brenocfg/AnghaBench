#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uiAreaMouseEvent ;
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiArea ;
struct TYPE_2__ {int /*<<< orphan*/  (* mouse ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t curExample ; 
 TYPE_1__** examples ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handlerMouseEvent(uiAreaHandler *a, uiArea *area, uiAreaMouseEvent *e)
{
	if (examples[curExample]->mouse != NULL)
		examples[curExample]->mouse(e);
}