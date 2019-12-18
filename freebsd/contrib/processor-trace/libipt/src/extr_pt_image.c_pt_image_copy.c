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
struct TYPE_2__ {int /*<<< orphan*/  vaddr; int /*<<< orphan*/  asid; int /*<<< orphan*/  section; } ;
struct pt_section_list {int /*<<< orphan*/  isid; TYPE_1__ section; struct pt_section_list* next; } ;
typedef  struct pt_image {struct pt_section_list* sections; } const pt_image ;

/* Variables and functions */
 int pt_image_add (struct pt_image const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pte_invalid ; 

int pt_image_copy(struct pt_image *image, const struct pt_image *src)
{
	struct pt_section_list *list;
	int ignored;

	if (!image || !src)
		return -pte_invalid;

	/* There is nothing to do if we copy an image to itself.
	 *
	 * Besides, pt_image_add() may move sections around, which would
	 * interfere with our section iteration.
	 */
	if (image == src)
		return 0;

	ignored = 0;
	for (list = src->sections; list; list = list->next) {
		int errcode;

		errcode = pt_image_add(image, list->section.section,
				       &list->section.asid,
				       list->section.vaddr,
				       list->isid);
		if (errcode < 0)
			ignored += 1;
	}

	return ignored;
}