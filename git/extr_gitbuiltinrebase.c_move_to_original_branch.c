#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; } ;
struct rebase_options {int /*<<< orphan*/  head_name; TYPE_2__* onto; } ;
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  RESET_HEAD_REFS_ONLY ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int reset_head (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int move_to_original_branch(struct rebase_options *opts)
{
	struct strbuf orig_head_reflog = STRBUF_INIT, head_reflog = STRBUF_INIT;
	int ret;

	if (!opts->head_name)
		return 0; /* nothing to move back to */

	if (!opts->onto)
		BUG("move_to_original_branch without onto");

	strbuf_addf(&orig_head_reflog, "rebase finished: %s onto %s",
		    opts->head_name, oid_to_hex(&opts->onto->object.oid));
	strbuf_addf(&head_reflog, "rebase finished: returning to %s",
		    opts->head_name);
	ret = reset_head(NULL, "", opts->head_name, RESET_HEAD_REFS_ONLY,
			 orig_head_reflog.buf, head_reflog.buf);

	strbuf_release(&orig_head_reflog);
	strbuf_release(&head_reflog);
	return ret;
}