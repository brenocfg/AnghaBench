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
struct json_writer {int /*<<< orphan*/  json; scalar_t__ pretty; } ;

/* Variables and functions */
 int /*<<< orphan*/  append_quoted_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  assert_in_object (struct json_writer*,char const*) ; 
 int /*<<< orphan*/  indent_pretty (struct json_writer*) ; 
 int /*<<< orphan*/  maybe_add_comma (struct json_writer*) ; 
 int /*<<< orphan*/  strbuf_addch (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void object_common(struct json_writer *jw, const char *key)
{
	assert_in_object(jw, key);
	maybe_add_comma(jw);

	if (jw->pretty) {
		strbuf_addch(&jw->json, '\n');
		indent_pretty(jw);
	}

	append_quoted_string(&jw->json, key);
	strbuf_addch(&jw->json, ':');
	if (jw->pretty)
		strbuf_addch(&jw->json, ' ');
}