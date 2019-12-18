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
struct ucl_emitter_context {int dummy; } ;
typedef  enum ucl_emitter { ____Placeholder_ucl_emitter } ucl_emitter ;

/* Variables and functions */
 int UCL_EMIT_JSON ; 
 int UCL_EMIT_MAX ; 
 struct ucl_emitter_context const* ucl_standard_emitters ; 

const struct ucl_emitter_context *
ucl_emit_get_standard_context (enum ucl_emitter emit_type)
{
	if (emit_type >= UCL_EMIT_JSON && emit_type < UCL_EMIT_MAX) {
		return &ucl_standard_emitters[emit_type];
	}

	return NULL;
}