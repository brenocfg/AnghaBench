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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct ref_store {int dummy; } ;
typedef  int /*<<< orphan*/  each_ref_fn ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int refs_for_each_fullref_in (struct ref_store*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int for_each_bisect_ref(struct ref_store *refs, each_ref_fn fn,
			       void *cb_data, const char *term)
{
	struct strbuf bisect_refs = STRBUF_INIT;
	int status;
	strbuf_addf(&bisect_refs, "refs/bisect/%s", term);
	status = refs_for_each_fullref_in(refs, bisect_refs.buf, fn, cb_data, 0);
	strbuf_release(&bisect_refs);
	return status;
}