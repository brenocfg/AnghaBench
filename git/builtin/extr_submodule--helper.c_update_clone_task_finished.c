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
struct TYPE_2__ {int nr; struct cache_entry const** entries; } ;
struct submodule_update_clone {int quickstop; struct cache_entry const** failed_clones; TYPE_1__ list; scalar_t__ failed_clones_nr; int /*<<< orphan*/  failed_clones_alloc; } ;
struct strbuf {int dummy; } ;
typedef  struct cache_entry {int /*<<< orphan*/  name; } const cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cache_entry const**,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_clone_task_finished(int result,
				      struct strbuf *err,
				      void *suc_cb,
				      void *idx_task_cb)
{
	const struct cache_entry *ce;
	struct submodule_update_clone *suc = suc_cb;

	int *idxP = idx_task_cb;
	int idx = *idxP;
	free(idxP);

	if (!result)
		return 0;

	if (idx < suc->list.nr) {
		ce  = suc->list.entries[idx];
		strbuf_addf(err, _("Failed to clone '%s'. Retry scheduled"),
			    ce->name);
		strbuf_addch(err, '\n');
		ALLOC_GROW(suc->failed_clones,
			   suc->failed_clones_nr + 1,
			   suc->failed_clones_alloc);
		suc->failed_clones[suc->failed_clones_nr++] = ce;
		return 0;
	} else {
		idx -= suc->list.nr;
		ce  = suc->failed_clones[idx];
		strbuf_addf(err, _("Failed to clone '%s' a second time, aborting"),
			    ce->name);
		strbuf_addch(err, '\n');
		suc->quickstop = 1;
		return 1;
	}

	return 0;
}