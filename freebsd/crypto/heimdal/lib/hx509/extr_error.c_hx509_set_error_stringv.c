#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  TYPE_1__* hx509_error ;
typedef  TYPE_2__* hx509_context ;
struct TYPE_9__ {TYPE_1__* error; } ;
struct TYPE_8__ {int code; struct TYPE_8__* next; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int HX509_ERROR_APPEND ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_error_string (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_clear_error_string (TYPE_2__*) ; 
 int vasprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void
hx509_set_error_stringv(hx509_context context, int flags, int code,
			const char *fmt, va_list ap)
{
    hx509_error msg;

    if (context == NULL)
	return;

    msg = calloc(1, sizeof(*msg));
    if (msg == NULL) {
	hx509_clear_error_string(context);
	return;
    }

    if (vasprintf(&msg->msg, fmt, ap) == -1) {
	hx509_clear_error_string(context);
	free(msg);
	return;
    }
    msg->code = code;

    if (flags & HX509_ERROR_APPEND) {
	msg->next = context->error;
	context->error = msg;
    } else  {
	free_error_string(context->error);
	context->error = msg;
    }
}