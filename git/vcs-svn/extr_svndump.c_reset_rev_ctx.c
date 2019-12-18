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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  note; int /*<<< orphan*/  author; int /*<<< orphan*/  log; scalar_t__ timestamp; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 TYPE_1__ rev_ctx ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_rev_ctx(uint32_t revision)
{
	rev_ctx.revision = revision;
	rev_ctx.timestamp = 0;
	strbuf_reset(&rev_ctx.log);
	strbuf_reset(&rev_ctx.author);
	strbuf_reset(&rev_ctx.note);
}