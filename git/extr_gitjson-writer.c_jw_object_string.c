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
struct json_writer {int /*<<< orphan*/  json; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_quoted_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  object_common (struct json_writer*,char const*) ; 

void jw_object_string(struct json_writer *jw, const char *key, const char *value)
{
	object_common(jw, key);
	append_quoted_string(&jw->json, value);
}