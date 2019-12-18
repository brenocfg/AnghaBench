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
struct json_writer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_sub_jw (struct json_writer*,struct json_writer const*) ; 
 int /*<<< orphan*/  array_common (struct json_writer*) ; 
 int /*<<< orphan*/  assert_is_terminated (struct json_writer const*) ; 

void jw_array_sub_jw(struct json_writer *jw, const struct json_writer *value)
{
	assert_is_terminated(value);

	array_common(jw);
	append_sub_jw(jw, value);
}