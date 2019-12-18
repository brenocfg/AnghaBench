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
struct ucl_emitter_functions {int /*<<< orphan*/  ud; int /*<<< orphan*/  (* ucl_emitter_append_character ) (char,unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ucl_add_tabs (const struct ucl_emitter_functions *func, unsigned int tabs,
		bool compact)
{
	if (!compact && tabs > 0) {
		func->ucl_emitter_append_character (' ', tabs * 4, func->ud);
	}
}