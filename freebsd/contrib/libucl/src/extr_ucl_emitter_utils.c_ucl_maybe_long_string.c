#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sv; } ;
struct TYPE_5__ {scalar_t__ len; int flags; TYPE_1__ value; } ;
typedef  TYPE_2__ ucl_object_t ;

/* Variables and functions */
 scalar_t__ LONG_STRING_LIMIT ; 
 int UCL_OBJECT_MULTILINE ; 
 int /*<<< orphan*/ * memchr (int /*<<< orphan*/ ,char,scalar_t__) ; 

bool
ucl_maybe_long_string (const ucl_object_t *obj)
{
	if (obj->len > LONG_STRING_LIMIT || (obj->flags & UCL_OBJECT_MULTILINE)) {
		/* String is long enough, so search for newline characters in it */
		if (memchr (obj->value.sv, '\n', obj->len) != NULL) {
			return true;
		}
	}

	return false;
}