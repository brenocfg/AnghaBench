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
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiAreaDrawParams ;
typedef  int /*<<< orphan*/  uiArea ;
struct TYPE_2__ {int /*<<< orphan*/  (* draw ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t curExample ; 
 TYPE_1__** examples ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handlerDraw(uiAreaHandler *a, uiArea *area, uiAreaDrawParams *p)
{
	examples[curExample]->draw(p);
}