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
struct TYPE_3__ {int /*<<< orphan*/  timebox; int /*<<< orphan*/  box; int /*<<< orphan*/  hasTime; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_container_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setDateOnly(uiprivDateTimePickerWidget *d)
{
	d->hasTime = FALSE;
	gtk_container_remove(GTK_CONTAINER(d->box), d->timebox);
}