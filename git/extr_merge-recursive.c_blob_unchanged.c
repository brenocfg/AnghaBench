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
struct merge_options {TYPE_1__* repo; } ;
struct index_state {int dummy; } ;
struct diff_filespec {scalar_t__ mode; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {struct index_state* index; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ oid_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read_oid_strbuf (struct merge_options*,int /*<<< orphan*/ *,struct strbuf*) ; 
 int renormalize_buffer (struct index_state const*,char const*,int /*<<< orphan*/ ,scalar_t__,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int blob_unchanged(struct merge_options *opt,
			  const struct diff_filespec *o,
			  const struct diff_filespec *a,
			  int renormalize, const char *path)
{
	struct strbuf obuf = STRBUF_INIT;
	struct strbuf abuf = STRBUF_INIT;
	int ret = 0; /* assume changed for safety */
	const struct index_state *idx = opt->repo->index;

	if (a->mode != o->mode)
		return 0;
	if (oid_eq(&o->oid, &a->oid))
		return 1;
	if (!renormalize)
		return 0;

	if (read_oid_strbuf(opt, &o->oid, &obuf) ||
	    read_oid_strbuf(opt, &a->oid, &abuf))
		goto error_return;
	/*
	 * Note: binary | is used so that both renormalizations are
	 * performed.  Comparison can be skipped if both files are
	 * unchanged since their sha1s have already been compared.
	 */
	if (renormalize_buffer(idx, path, obuf.buf, obuf.len, &obuf) |
	    renormalize_buffer(idx, path, abuf.buf, abuf.len, &abuf))
		ret = (obuf.len == abuf.len && !memcmp(obuf.buf, abuf.buf, obuf.len));

error_return:
	strbuf_release(&obuf);
	strbuf_release(&abuf);
	return ret;
}