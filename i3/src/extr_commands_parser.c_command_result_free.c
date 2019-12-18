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
struct TYPE_4__ {struct TYPE_4__* error_message; } ;
typedef  TYPE_1__ CommandResult ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 

void command_result_free(CommandResult *result) {
    if (result == NULL)
        return;

    FREE(result->error_message);
    FREE(result);
}