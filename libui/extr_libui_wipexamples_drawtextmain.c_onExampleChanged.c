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
typedef  int /*<<< orphan*/  uiCombobox ;
struct TYPE_2__ {int /*<<< orphan*/  panel; } ;

/* Variables and functions */
 size_t curExample ; 
 int /*<<< orphan*/  exampleList ; 
 TYPE_1__** examples ; 
 int /*<<< orphan*/  redraw () ; 
 size_t uiComboboxSelected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlHide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlShow (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void onExampleChanged(uiCombobox *c, void *data)
{
	uiControlHide(examples[curExample]->panel);
	curExample = uiComboboxSelected(exampleList);
	uiControlShow(examples[curExample]->panel);
	redraw();
}