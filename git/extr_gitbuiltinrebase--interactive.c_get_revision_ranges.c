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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 char* find_unique_abbrev (struct object_id*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 char* xstrdup (char const*) ; 
 char* xstrfmt (char*,char const*,char const*) ; 

__attribute__((used)) static int get_revision_ranges(const char *upstream, const char *onto,
			       const char **head_hash,
			       char **revisions, char **shortrevisions)
{
	const char *base_rev = upstream ? upstream : onto, *shorthead;
	struct object_id orig_head;

	if (get_oid("HEAD", &orig_head))
		return error(_("no HEAD?"));

	*head_hash = find_unique_abbrev(&orig_head, GIT_MAX_HEXSZ);
	*revisions = xstrfmt("%s...%s", base_rev, *head_hash);

	shorthead = find_unique_abbrev(&orig_head, DEFAULT_ABBREV);

	if (upstream) {
		const char *shortrev;
		struct object_id rev_oid;

		get_oid(base_rev, &rev_oid);
		shortrev = find_unique_abbrev(&rev_oid, DEFAULT_ABBREV);

		*shortrevisions = xstrfmt("%s..%s", shortrev, shorthead);
	} else
		*shortrevisions = xstrdup(shorthead);

	return 0;
}