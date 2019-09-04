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
struct submodule_cache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * command; int /*<<< orphan*/  type; } ;
struct submodule {int recommend_shallow; int /*<<< orphan*/  gitmodules_oid; int /*<<< orphan*/ * branch; int /*<<< orphan*/ * ignore; int /*<<< orphan*/  fetch_recurse; TYPE_1__ update_strategy; int /*<<< orphan*/ * url; int /*<<< orphan*/ * path; int /*<<< orphan*/  name; } ;
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECURSE_SUBMODULES_NONE ; 
 int /*<<< orphan*/  SM_UPDATE_UNSPECIFIED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  cache_add (struct submodule_cache*,struct submodule*) ; 
 struct submodule* cache_lookup_name (struct submodule_cache*,struct object_id const*,char const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 struct submodule* xmalloc (int) ; 

__attribute__((used)) static struct submodule *lookup_or_create_by_name(struct submodule_cache *cache,
		const struct object_id *gitmodules_oid, const char *name)
{
	struct submodule *submodule;
	struct strbuf name_buf = STRBUF_INIT;

	submodule = cache_lookup_name(cache, gitmodules_oid, name);
	if (submodule)
		return submodule;

	submodule = xmalloc(sizeof(*submodule));

	strbuf_addstr(&name_buf, name);
	submodule->name = strbuf_detach(&name_buf, NULL);

	submodule->path = NULL;
	submodule->url = NULL;
	submodule->update_strategy.type = SM_UPDATE_UNSPECIFIED;
	submodule->update_strategy.command = NULL;
	submodule->fetch_recurse = RECURSE_SUBMODULES_NONE;
	submodule->ignore = NULL;
	submodule->branch = NULL;
	submodule->recommend_shallow = -1;

	oidcpy(&submodule->gitmodules_oid, gitmodules_oid);

	cache_add(cache, submodule);

	return submodule;
}