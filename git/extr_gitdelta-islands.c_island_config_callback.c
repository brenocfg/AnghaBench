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

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int config_error_nonbool (char const*) ; 
 int /*<<< orphan*/  core_island_name ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int git_config_string (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/ * island_regexes ; 
 int /*<<< orphan*/  island_regexes_alloc ; 
 int island_regexes_nr ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int island_config_callback(const char *k, const char *v, void *cb)
{
	if (!strcmp(k, "pack.island")) {
		struct strbuf re = STRBUF_INIT;

		if (!v)
			return config_error_nonbool(k);

		ALLOC_GROW(island_regexes, island_regexes_nr + 1, island_regexes_alloc);

		if (*v != '^')
			strbuf_addch(&re, '^');
		strbuf_addstr(&re, v);

		if (regcomp(&island_regexes[island_regexes_nr], re.buf, REG_EXTENDED))
			die(_("failed to load island regex for '%s': %s"), k, re.buf);

		strbuf_release(&re);
		island_regexes_nr++;
		return 0;
	}

	if (!strcmp(k, "pack.islandcore"))
		return git_config_string(&core_island_name, k, v);

	return 0;
}