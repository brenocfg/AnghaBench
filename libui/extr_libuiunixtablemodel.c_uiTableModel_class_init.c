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
typedef  int /*<<< orphan*/  uiTableModelClass ;
struct TYPE_2__ {int /*<<< orphan*/  finalize; int /*<<< orphan*/  dispose; } ;

/* Variables and functions */
 TYPE_1__* G_OBJECT_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiTableModel_dispose ; 
 int /*<<< orphan*/  uiTableModel_finalize ; 

__attribute__((used)) static void uiTableModel_class_init(uiTableModelClass *class)
{
	G_OBJECT_CLASS(class)->dispose = uiTableModel_dispose;
	G_OBJECT_CLASS(class)->finalize = uiTableModel_finalize;
}