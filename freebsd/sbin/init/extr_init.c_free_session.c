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
struct TYPE_4__ {struct TYPE_4__* se_type; struct TYPE_4__* se_window_argv; struct TYPE_4__* se_window_argv_space; struct TYPE_4__* se_window; struct TYPE_4__* se_getty_argv; struct TYPE_4__* se_getty_argv_space; struct TYPE_4__* se_getty; struct TYPE_4__* se_device; } ;
typedef  TYPE_1__ session_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
free_session(session_t *sp)
{
	free(sp->se_device);
	if (sp->se_getty) {
		free(sp->se_getty);
		free(sp->se_getty_argv_space);
		free(sp->se_getty_argv);
	}
	if (sp->se_window) {
		free(sp->se_window);
		free(sp->se_window_argv_space);
		free(sp->se_window_argv);
	}
	if (sp->se_type)
		free(sp->se_type);
	free(sp);
}