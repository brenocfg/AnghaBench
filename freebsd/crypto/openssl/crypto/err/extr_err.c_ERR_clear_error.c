#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_1__ ERR_STATE ;

/* Variables and functions */
 int ERR_NUM_ERRORS ; 
 TYPE_1__* ERR_get_state () ; 
 int /*<<< orphan*/  err_clear (TYPE_1__*,int) ; 

void ERR_clear_error(void)
{
    int i;
    ERR_STATE *es;

    es = ERR_get_state();
    if (es == NULL)
        return;

    for (i = 0; i < ERR_NUM_ERRORS; i++) {
        err_clear(es, i);
    }
    es->top = es->bottom = 0;
}