#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; char* buf; } ;
struct json_writer {TYPE_1__ open_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*) ; 

__attribute__((used)) static void assert_in_object(const struct json_writer *jw, const char *key)
{
	if (!jw->open_stack.len)
		BUG("json-writer: object: missing jw_object_begin(): '%s'", key);
	if (jw->open_stack.buf[jw->open_stack.len - 1] != '{')
		BUG("json-writer: object: not in object: '%s'", key);
}