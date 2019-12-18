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
struct TYPE_2__ {int len; } ;
struct json_writer {int /*<<< orphan*/  json; TYPE_1__ open_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void indent_pretty(struct json_writer *jw)
{
	int k;

	for (k = 0; k < jw->open_stack.len; k++)
		strbuf_addstr(&jw->json, "  ");
}