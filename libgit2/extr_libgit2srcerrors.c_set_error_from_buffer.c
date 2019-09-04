#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int klass; int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ git_error ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_6__ {TYPE_1__* last_error; TYPE_2__ error_buf; TYPE_1__ error_t; } ;

/* Variables and functions */
 TYPE_3__* GIT_GLOBAL ; 

__attribute__((used)) static void set_error_from_buffer(int error_class)
{
	git_error *error = &GIT_GLOBAL->error_t;
	git_buf *buf = &GIT_GLOBAL->error_buf;

	error->message = buf->ptr;
	error->klass = error_class;

	GIT_GLOBAL->last_error = error;
}