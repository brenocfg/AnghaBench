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
struct strbuf {int dummy; } ;
struct repository {int /*<<< orphan*/  submodule_prefix; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 

__attribute__((used)) static void construct_fullname(struct strbuf *out, const struct repository *repo,
			       const struct cache_entry *ce)
{
	strbuf_reset(out);
	if (repo->submodule_prefix)
		strbuf_addstr(out, repo->submodule_prefix);
	strbuf_addstr(out, ce->name);
}