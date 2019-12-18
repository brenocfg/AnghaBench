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
struct ptunit_result {int dummy; } ;
struct pt_section {int ucount; int mcount; } ;
struct pt_image {int dummy; } ;
struct pt_asid {int dummy; } ;
struct ifix_status {int deleted; int bad_put; } ;
struct ifix_mapping {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifix_init_section (struct pt_section*,int /*<<< orphan*/ *,struct ifix_status*,struct ifix_mapping*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_asid_init (struct pt_asid*) ; 
 int pt_image_add (struct pt_image*,struct pt_section*,struct pt_asid*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_image_fini (struct pt_image*) ; 
 int /*<<< orphan*/  pt_image_init (struct pt_image*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_int_eq (int,int) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result fini(void)
{
	struct ifix_mapping mapping;
	struct ifix_status status;
	struct pt_section section;
	struct pt_image image;
	struct pt_asid asid;
	int errcode;

	pt_asid_init(&asid);
	ifix_init_section(&section, NULL, &status, &mapping, NULL);

	pt_image_init(&image, NULL);
	errcode = pt_image_add(&image, &section, &asid, 0x0ull, 0);
	ptu_int_eq(errcode, 0);

	pt_image_fini(&image);
	ptu_int_eq(section.ucount, 0);
	ptu_int_eq(section.mcount, 0);
	ptu_int_eq(status.deleted, 1);
	ptu_int_eq(status.bad_put, 0);

	return ptu_passed();
}