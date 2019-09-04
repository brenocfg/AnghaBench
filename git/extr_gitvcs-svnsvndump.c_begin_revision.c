#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  buf; } ;
struct TYPE_10__ {TYPE_3__ url; TYPE_2__ uuid; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  log; TYPE_1__ author; int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 TYPE_5__ dump_ctx ; 
 int /*<<< orphan*/  fast_export_begin_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_4__ rev_ctx ; 

__attribute__((used)) static void begin_revision(const char *remote_ref)
{
	if (!rev_ctx.revision)	/* revision 0 gets no git commit. */
		return;
	fast_export_begin_commit(rev_ctx.revision, rev_ctx.author.buf,
		&rev_ctx.log, dump_ctx.uuid.buf, dump_ctx.url.buf,
		rev_ctx.timestamp, remote_ref);
}