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
struct TYPE_2__ {int version; int /*<<< orphan*/  uuid; int /*<<< orphan*/  url; } ;

/* Variables and functions */
 TYPE_1__ dump_ctx ; 
 int /*<<< orphan*/  strbuf_addstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_dump_ctx(const char *url)
{
	strbuf_reset(&dump_ctx.url);
	if (url)
		strbuf_addstr(&dump_ctx.url, url);
	dump_ctx.version = 1;
	strbuf_reset(&dump_ctx.uuid);
}