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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_section_list {int isid; int /*<<< orphan*/  section; } ;
struct pt_section {int dummy; } ;
struct pt_asid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_section_list*) ; 
 struct pt_section_list* malloc (int) ; 
 int /*<<< orphan*/  memset (struct pt_section_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_msec_init (int /*<<< orphan*/ *,struct pt_section*,struct pt_asid const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pt_section_get (struct pt_section*) ; 

__attribute__((used)) static struct pt_section_list *pt_mk_section_list(struct pt_section *section,
						  const struct pt_asid *asid,
						  uint64_t vaddr,
						  uint64_t offset,
						  uint64_t size, int isid)
{
	struct pt_section_list *list;
	int errcode;

	list = malloc(sizeof(*list));
	if (!list)
		return NULL;

	memset(list, 0, sizeof(*list));

	errcode = pt_section_get(section);
	if (errcode < 0)
		goto out_mem;

	pt_msec_init(&list->section, section, asid, vaddr, offset, size);
	list->isid = isid;

	return list;

out_mem:
	free(list);
	return NULL;
}