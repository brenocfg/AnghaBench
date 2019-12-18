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
typedef  TYPE_1__* hx509_context ;
struct TYPE_3__ {int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_error_string (int /*<<< orphan*/ *) ; 

void
hx509_clear_error_string(hx509_context context)
{
    if (context) {
	free_error_string(context->error);
	context->error = NULL;
    }
}