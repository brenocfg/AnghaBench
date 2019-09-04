#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* pages; } ;
typedef  TYPE_2__ uiTab ;
typedef  int /*<<< orphan*/  uiControl ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  uiTabInsertAt (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void uiTabAppend(uiTab *t, const char *name, uiControl *child)
{
	uiTabInsertAt(t, name, t->pages->len, child);
}