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
struct string_list {int nr; TYPE_1__* items; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct rerere_id {scalar_t__ variant; } ;
struct TYPE_2__ {int /*<<< orphan*/  string; struct rerere_id* util; } ;

/* Variables and functions */
 struct rerere_id* RERERE_RESOLVED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ commit_lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rerere_id_hex (struct rerere_id*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ write_in_full (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock ; 

__attribute__((used)) static int write_rr(struct string_list *rr, int out_fd)
{
	int i;
	for (i = 0; i < rr->nr; i++) {
		struct strbuf buf = STRBUF_INIT;
		struct rerere_id *id;

		assert(rr->items[i].util != RERERE_RESOLVED);

		id = rr->items[i].util;
		if (!id)
			continue;
		assert(id->variant >= 0);
		if (0 < id->variant)
			strbuf_addf(&buf, "%s.%d\t%s%c",
				    rerere_id_hex(id), id->variant,
				    rr->items[i].string, 0);
		else
			strbuf_addf(&buf, "%s\t%s%c",
				    rerere_id_hex(id),
				    rr->items[i].string, 0);

		if (write_in_full(out_fd, buf.buf, buf.len) < 0)
			die(_("unable to write rerere record"));

		strbuf_release(&buf);
	}
	if (commit_lock_file(&write_lock) != 0)
		die(_("unable to write rerere record"));
	return 0;
}