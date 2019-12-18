#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; scalar_t__ len; } ;
struct object_id {int dummy; } ;
struct TYPE_4__ {int rm_so; scalar_t__ rm_eo; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_ref_to_island (int /*<<< orphan*/ ,struct object_id const*) ; 
 int /*<<< orphan*/ * island_regexes ; 
 int island_regexes_nr ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_island_for_ref(const char *refname, const struct object_id *oid,
			       int flags, void *data)
{
	/*
	 * We should advertise 'ARRAY_SIZE(matches) - 2' as the max,
	 * so we can diagnose below a config with more capture groups
	 * than we support.
	 */
	regmatch_t matches[16];
	int i, m;
	struct strbuf island_name = STRBUF_INIT;

	/* walk backwards to get last-one-wins ordering */
	for (i = island_regexes_nr - 1; i >= 0; i--) {
		if (!regexec(&island_regexes[i], refname,
			     ARRAY_SIZE(matches), matches, 0))
			break;
	}

	if (i < 0)
		return 0;

	if (matches[ARRAY_SIZE(matches) - 1].rm_so != -1)
		warning(_("island regex from config has "
			  "too many capture groups (max=%d)"),
			(int)ARRAY_SIZE(matches) - 2);

	for (m = 1; m < ARRAY_SIZE(matches); m++) {
		regmatch_t *match = &matches[m];

		if (match->rm_so == -1)
			continue;

		if (island_name.len)
			strbuf_addch(&island_name, '-');

		strbuf_add(&island_name, refname + match->rm_so, match->rm_eo - match->rm_so);
	}

	add_ref_to_island(island_name.buf, oid);
	strbuf_release(&island_name);
	return 0;
}