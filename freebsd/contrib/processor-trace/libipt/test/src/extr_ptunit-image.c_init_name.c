#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ptunit_result {int dummy; } ;
struct TYPE_4__ {void* context; scalar_t__ callback; } ;
struct TYPE_5__ {void* sections; TYPE_1__ readmem; int /*<<< orphan*/  name; } ;
struct image_fixture {TYPE_2__ image; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  pt_image_init (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ptu_null (void*) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_str_eq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ptunit_result init_name(struct image_fixture *ifix)
{
	memset(&ifix->image, 0xcd, sizeof(ifix->image));

	pt_image_init(&ifix->image, "image-name");
	ptu_str_eq(ifix->image.name, "image-name");
	ptu_null(ifix->image.sections);
	ptu_null((void *) (uintptr_t) ifix->image.readmem.callback);
	ptu_null(ifix->image.readmem.context);

	return ptu_passed();
}