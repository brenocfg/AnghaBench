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
struct json_writer {scalar_t__ pretty; scalar_t__ need_comma; int /*<<< orphan*/  open_stack; int /*<<< orphan*/  json; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void jw_init(struct json_writer *jw)
{
	strbuf_init(&jw->json, 0);
	strbuf_init(&jw->open_stack, 0);
	jw->need_comma = 0;
	jw->pretty = 0;
}