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
struct TYPE_3__ {int /*<<< orphan*/ * strings; } ;
typedef  TYPE_1__ UI ;

/* Variables and functions */
 int /*<<< orphan*/ * sk_UI_STRING_new_null () ; 

__attribute__((used)) static int allocate_string_stack(UI *ui)
{
    if (ui->strings == NULL) {
        ui->strings = sk_UI_STRING_new_null();
        if (ui->strings == NULL) {
            return -1;
        }
    }
    return 0;
}