#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uis ;
struct TYPE_9__ {char const* out_string; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ UI_STRING ;
struct TYPE_10__ {TYPE_1__* meth; } ;
typedef  TYPE_3__ UI ;
struct TYPE_8__ {scalar_t__ (* ui_write_string ) (TYPE_3__*,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  UIT_ERROR ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_2__*) ; 

__attribute__((used)) static int print_error(const char *str, size_t len, UI *ui)
{
    UI_STRING uis;

    memset(&uis, 0, sizeof(uis));
    uis.type = UIT_ERROR;
    uis.out_string = str;

    if (ui->meth->ui_write_string != NULL
        && ui->meth->ui_write_string(ui, &uis) <= 0)
        return -1;
    return 0;
}