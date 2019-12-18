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
 int /*<<< orphan*/  BUG (char*) ; 

__attribute__((used)) static void assert_in_array(const struct json_writer *jw)
{
	if (!jw->open_stack.len)
		BUG("json-writer: array: missing jw_array_begin()");
	if (jw->open_stack.buf[jw->open_stack.len - 1] != '[')
		BUG("json-writer: array: not in array");
}