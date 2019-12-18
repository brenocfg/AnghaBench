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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref_transaction {int dummy; } ;
struct ref {int /*<<< orphan*/  old_oid; TYPE_1__* peer_ref; struct ref* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ initial_ref_transaction_commit (struct ref_transaction*,struct strbuf*) ; 
 struct ref_transaction* ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_create (struct ref_transaction*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (struct ref_transaction*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void write_remote_refs(const struct ref *local_refs)
{
	const struct ref *r;

	struct ref_transaction *t;
	struct strbuf err = STRBUF_INIT;

	t = ref_transaction_begin(&err);
	if (!t)
		die("%s", err.buf);

	for (r = local_refs; r; r = r->next) {
		if (!r->peer_ref)
			continue;
		if (ref_transaction_create(t, r->peer_ref->name, &r->old_oid,
					   0, NULL, &err))
			die("%s", err.buf);
	}

	if (initial_ref_transaction_commit(t, &err))
		die("%s", err.buf);

	strbuf_release(&err);
	ref_transaction_free(t);
}