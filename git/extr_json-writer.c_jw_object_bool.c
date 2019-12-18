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
 int /*<<< orphan*/  jw_object_false (struct json_writer*,char const*) ; 
 int /*<<< orphan*/  jw_object_true (struct json_writer*,char const*) ; 

void jw_object_bool(struct json_writer *jw, const char *key, int value)
{
	if (value)
		jw_object_true(jw, key);
	else
		jw_object_false(jw, key);
}