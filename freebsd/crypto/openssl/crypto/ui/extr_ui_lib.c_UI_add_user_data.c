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
struct TYPE_6__ {int flags; void* user_data; TYPE_1__* meth; } ;
typedef  TYPE_2__ UI ;
struct TYPE_5__ {int /*<<< orphan*/  (* ui_destroy_data ) (TYPE_2__*,void*) ;} ;

/* Variables and functions */
 int UI_FLAG_DUPL_DATA ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,void*) ; 

void *UI_add_user_data(UI *ui, void *user_data)
{
    void *old_data = ui->user_data;

    if ((ui->flags & UI_FLAG_DUPL_DATA) != 0) {
        ui->meth->ui_destroy_data(ui, old_data);
        old_data = NULL;
    }
    ui->user_data = user_data;
    ui->flags &= ~UI_FLAG_DUPL_DATA;
    return old_data;
}