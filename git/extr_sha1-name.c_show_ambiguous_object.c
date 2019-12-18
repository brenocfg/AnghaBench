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
struct tag {scalar_t__ tag; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct pretty_print_context {TYPE_1__ date_mode; int /*<<< orphan*/  member_0; } ;
struct object_id {int dummy; } ;
struct disambiguate_state {int /*<<< orphan*/  repo; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* fn ) (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ ) ;} ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_SHORT ; 
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int OBJ_COMMIT ; 
 int OBJ_TAG ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  advise (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_commit_message (struct commit*,char*,struct strbuf*,struct pretty_print_context*) ; 
 struct commit* lookup_commit (int /*<<< orphan*/ ,struct object_id const*) ; 
 struct tag* lookup_tag (int /*<<< orphan*/ ,struct object_id const*) ; 
 int oid_object_info (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_tag (struct tag*) ; 
 int /*<<< orphan*/  repo_find_unique_abbrev (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct object_id const*,int /*<<< orphan*/ ) ; 
 char* type_name (int) ; 

__attribute__((used)) static int show_ambiguous_object(const struct object_id *oid, void *data)
{
	const struct disambiguate_state *ds = data;
	struct strbuf desc = STRBUF_INIT;
	int type;

	if (ds->fn && !ds->fn(ds->repo, oid, ds->cb_data))
		return 0;

	type = oid_object_info(ds->repo, oid, NULL);
	if (type == OBJ_COMMIT) {
		struct commit *commit = lookup_commit(ds->repo, oid);
		if (commit) {
			struct pretty_print_context pp = {0};
			pp.date_mode.type = DATE_SHORT;
			format_commit_message(commit, " %ad - %s", &desc, &pp);
		}
	} else if (type == OBJ_TAG) {
		struct tag *tag = lookup_tag(ds->repo, oid);
		if (!parse_tag(tag) && tag->tag)
			strbuf_addf(&desc, " %s", tag->tag);
	}

	advise("  %s %s%s",
	       repo_find_unique_abbrev(ds->repo, oid, DEFAULT_ABBREV),
	       type_name(type) ? type_name(type) : "unknown type",
	       desc.buf);

	strbuf_release(&desc);
	return 0;
}