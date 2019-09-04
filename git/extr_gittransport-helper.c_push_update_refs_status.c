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
struct strbuf {int /*<<< orphan*/  len; } ;
struct ref {int /*<<< orphan*/  new_oid; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct helper_data {TYPE_1__ rs; scalar_t__ no_private_update; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int TRANSPORT_PUSH_DRY_RUN ; 
 char* apply_refspecs (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ push_update_ref_status (struct strbuf*,struct ref**,struct ref*) ; 
 scalar_t__ recvline (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  update_ref (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_update_refs_status(struct helper_data *data,
				    struct ref *remote_refs,
				    int flags)
{
	struct strbuf buf = STRBUF_INIT;
	struct ref *ref = remote_refs;
	int ret = 0;

	for (;;) {
		char *private;

		if (recvline(data, &buf)) {
			ret = 1;
			break;
		}

		if (!buf.len)
			break;

		if (push_update_ref_status(&buf, &ref, remote_refs))
			continue;

		if (flags & TRANSPORT_PUSH_DRY_RUN || !data->rs.nr || data->no_private_update)
			continue;

		/* propagate back the update to the remote namespace */
		private = apply_refspecs(&data->rs, ref->name);
		if (!private)
			continue;
		update_ref("update by helper", private, &ref->new_oid, NULL,
			   0, 0);
		free(private);
	}
	strbuf_release(&buf);
	return ret;
}