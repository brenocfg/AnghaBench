#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ type; scalar_t__ filled; scalar_t__ tagged; TYPE_1__* delta; struct TYPE_14__* delta_sibling; int /*<<< orphan*/ * delta_child; } ;
typedef  TYPE_2__ git_pobject ;
struct TYPE_15__ {size_t nr_objects; TYPE_2__* object_list; int /*<<< orphan*/  repo; } ;
typedef  TYPE_3__ git_packbuilder ;
struct TYPE_13__ {TYPE_2__* delta_child; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ GIT_OBJECT_COMMIT ; 
 scalar_t__ GIT_OBJECT_TAG ; 
 scalar_t__ GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  add_family_to_write_order (TYPE_2__**,size_t*,TYPE_2__*) ; 
 int /*<<< orphan*/  add_to_write_order (TYPE_2__**,size_t*,TYPE_2__*) ; 
 int /*<<< orphan*/  cb_tag_foreach ; 
 int /*<<< orphan*/  git__free (TYPE_2__**) ; 
 TYPE_2__** git__mallocarray (size_t,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_tag_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static git_pobject **compute_write_order(git_packbuilder *pb)
{
	size_t i, wo_end, last_untagged;
	git_pobject **wo;

	if ((wo = git__mallocarray(pb->nr_objects, sizeof(*wo))) == NULL)
		return NULL;

	for (i = 0; i < pb->nr_objects; i++) {
		git_pobject *po = pb->object_list + i;
		po->tagged = 0;
		po->filled = 0;
		po->delta_child = NULL;
		po->delta_sibling = NULL;
	}

	/*
	 * Fully connect delta_child/delta_sibling network.
	 * Make sure delta_sibling is sorted in the original
	 * recency order.
	 */
	for (i = pb->nr_objects; i > 0;) {
		git_pobject *po = &pb->object_list[--i];
		if (!po->delta)
			continue;
		/* Mark me as the first child */
		po->delta_sibling = po->delta->delta_child;
		po->delta->delta_child = po;
	}

	/*
	 * Mark objects that are at the tip of tags.
	 */
	if (git_tag_foreach(pb->repo, &cb_tag_foreach, pb) < 0) {
		git__free(wo);
		return NULL;
	}

	/*
	 * Give the objects in the original recency order until
	 * we see a tagged tip.
	 */
	for (i = wo_end = 0; i < pb->nr_objects; i++) {
		git_pobject *po = pb->object_list + i;
		if (po->tagged)
			break;
		add_to_write_order(wo, &wo_end, po);
	}
	last_untagged = i;

	/*
	 * Then fill all the tagged tips.
	 */
	for (; i < pb->nr_objects; i++) {
		git_pobject *po = pb->object_list + i;
		if (po->tagged)
			add_to_write_order(wo, &wo_end, po);
	}

	/*
	 * And then all remaining commits and tags.
	 */
	for (i = last_untagged; i < pb->nr_objects; i++) {
		git_pobject *po = pb->object_list + i;
		if (po->type != GIT_OBJECT_COMMIT &&
		    po->type != GIT_OBJECT_TAG)
			continue;
		add_to_write_order(wo, &wo_end, po);
	}

	/*
	 * And then all the trees.
	 */
	for (i = last_untagged; i < pb->nr_objects; i++) {
		git_pobject *po = pb->object_list + i;
		if (po->type != GIT_OBJECT_TREE)
			continue;
		add_to_write_order(wo, &wo_end, po);
	}

	/*
	 * Finally all the rest in really tight order
	 */
	for (i = last_untagged; i < pb->nr_objects; i++) {
		git_pobject *po = pb->object_list + i;
		if (!po->filled)
			add_family_to_write_order(wo, &wo_end, po);
	}

	if (wo_end != pb->nr_objects) {
		git__free(wo);
		git_error_set(GIT_ERROR_INVALID, "invalid write order");
		return NULL;
	}

	return wo;
}