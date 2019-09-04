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
struct repository {int dummy; } ;
struct index_state {int /*<<< orphan*/  cache_tree; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  verify_one (struct repository*,struct index_state*,int /*<<< orphan*/ ,struct strbuf*) ; 

void cache_tree_verify(struct repository *r, struct index_state *istate)
{
	struct strbuf path = STRBUF_INIT;

	if (!istate->cache_tree)
		return;
	verify_one(r, istate, istate->cache_tree, &path);
	strbuf_release(&path);
}