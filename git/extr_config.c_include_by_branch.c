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
struct TYPE_2__ {int /*<<< orphan*/  gitdir; } ;

/* Variables and functions */
 int REF_ISSYMREF ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WM_PATHNAME ; 
 int /*<<< orphan*/  add_trailing_starstar_for_dir (struct strbuf*) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_1__* the_repository ; 
 int /*<<< orphan*/  wildmatch (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int include_by_branch(const char *cond, size_t cond_len)
{
	int flags;
	int ret;
	struct strbuf pattern = STRBUF_INIT;
	const char *refname = !the_repository->gitdir ?
		NULL : resolve_ref_unsafe("HEAD", 0, NULL, &flags);
	const char *shortname;

	if (!refname || !(flags & REF_ISSYMREF)	||
			!skip_prefix(refname, "refs/heads/", &shortname))
		return 0;

	strbuf_add(&pattern, cond, cond_len);
	add_trailing_starstar_for_dir(&pattern);
	ret = !wildmatch(pattern.buf, shortname, WM_PATHNAME);
	strbuf_release(&pattern);
	return ret;
}