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
struct strbuf {char const* buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESOLVE_REF_READING ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,struct object_id*) ; 
 char** ref_rev_parse_rules ; 
 scalar_t__ reflog_exists (char const*) ; 
 char* resolve_ref_unsafe (char const*,int /*<<< orphan*/ ,struct object_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char const*,int,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* substitute_branch_name (char const**,int*) ; 
 int /*<<< orphan*/  warn_ambiguous_refs ; 
 char* xstrdup (char const*) ; 

int dwim_log(const char *str, int len, struct object_id *oid, char **log)
{
	char *last_branch = substitute_branch_name(&str, &len);
	const char **p;
	int logs_found = 0;
	struct strbuf path = STRBUF_INIT;

	*log = NULL;
	for (p = ref_rev_parse_rules; *p; p++) {
		struct object_id hash;
		const char *ref, *it;

		strbuf_reset(&path);
		strbuf_addf(&path, *p, len, str);
		ref = resolve_ref_unsafe(path.buf, RESOLVE_REF_READING,
					 &hash, NULL);
		if (!ref)
			continue;
		if (reflog_exists(path.buf))
			it = path.buf;
		else if (strcmp(ref, path.buf) && reflog_exists(ref))
			it = ref;
		else
			continue;
		if (!logs_found++) {
			*log = xstrdup(it);
			oidcpy(oid, &hash);
		}
		if (!warn_ambiguous_refs)
			break;
	}
	strbuf_release(&path);
	free(last_branch);
	return logs_found;
}