#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_free_func ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ucl_emitter_functions*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
ucl_object_emit_funcs_free (struct ucl_emitter_functions *f)
{
	if (f != NULL) {
		if (f->ucl_emitter_free_func != NULL) {
			f->ucl_emitter_free_func (f->ud);
		}
		free (f);
	}
}