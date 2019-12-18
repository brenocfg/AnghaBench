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
struct ptunit_result {int dummy; } ;
struct image_fixture {TYPE_1__* asid; scalar_t__ nsecs; int /*<<< orphan*/  iscache; int /*<<< orphan*/ * section; int /*<<< orphan*/ * mapping; int /*<<< orphan*/ * status; int /*<<< orphan*/  copy; int /*<<< orphan*/  image; } ;
struct TYPE_2__ {int cr3; } ;

/* Variables and functions */
 int ifix_add_section (struct image_fixture*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_asid_init (TYPE_1__*) ; 
 int /*<<< orphan*/  pt_image_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result ifix_init(struct image_fixture *ifix)
{
	int index;

	pt_image_init(&ifix->image, NULL);
	pt_image_init(&ifix->copy, NULL);

	memset(ifix->status, 0, sizeof(ifix->status));
	memset(ifix->mapping, 0, sizeof(ifix->mapping));
	memset(ifix->section, 0, sizeof(ifix->section));
	memset(&ifix->iscache, 0, sizeof(ifix->iscache));

	ifix->nsecs = 0;

	index = ifix_add_section(ifix, "file-0");
	ptu_int_eq(index, 0);

	index = ifix_add_section(ifix, "file-1");
	ptu_int_eq(index, 1);

	index = ifix_add_section(ifix, "file-2");
	ptu_int_eq(index, 2);

	pt_asid_init(&ifix->asid[0]);
	ifix->asid[0].cr3 = 0xa000;

	pt_asid_init(&ifix->asid[1]);
	ifix->asid[1].cr3 = 0xb000;

	pt_asid_init(&ifix->asid[2]);
	ifix->asid[2].cr3 = 0xc000;

	return ptu_passed();
}