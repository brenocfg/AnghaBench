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
typedef  int /*<<< orphan*/  ucl_object_t ;
typedef  enum ucl_emitter { ____Placeholder_ucl_emitter } ucl_emitter ;

/* Variables and functions */
 unsigned char* ucl_object_emit_len (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

unsigned char *
ucl_object_emit (const ucl_object_t *obj, enum ucl_emitter emit_type)
{
	return ucl_object_emit_len (obj, emit_type, NULL);
}