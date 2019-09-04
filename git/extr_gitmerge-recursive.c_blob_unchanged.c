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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct merge_options {TYPE_1__* repo; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ oid_eq (struct object_id const*,struct object_id const*) ; 
 scalar_t__ read_oid_strbuf (struct merge_options*,struct object_id const*,struct strbuf*) ; 
 int renormalize_buffer (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int blob_unchanged(struct merge_options *opt,
			  const struct object_id *o_oid,
			  unsigned o_mode,
			  const struct object_id *a_oid,
			  unsigned a_mode,
			  int renormalize, const char *path)
{
	struct strbuf o = STRBUF_INIT;
	struct strbuf a = STRBUF_INIT;
	int ret = 0; /* assume changed for safety */

	if (a_mode != o_mode)
		return 0;
	if (oid_eq(o_oid, a_oid))
		return 1;
	if (!renormalize)
		return 0;

	assert(o_oid && a_oid);
	if (read_oid_strbuf(opt, o_oid, &o) || read_oid_strbuf(opt, a_oid, &a))
		goto error_return;
	/*
	 * Note: binary | is used so that both renormalizations are
	 * performed.  Comparison can be skipped if both files are
	 * unchanged since their sha1s have already been compared.
	 */
	if (renormalize_buffer(opt->repo->index, path, o.buf, o.len, &o) |
	    renormalize_buffer(opt->repo->index, path, a.buf, a.len, &a))
		ret = (o.len == a.len && !memcmp(o.buf, a.buf, o.len));

error_return:
	strbuf_release(&o);
	strbuf_release(&a);
	return ret;
}