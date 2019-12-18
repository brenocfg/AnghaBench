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
struct TYPE_2__ {void* context; scalar_t__ callback; } ;
struct pt_image {void* name; void* sections; TYPE_1__ readmem; } ;
typedef  int /*<<< orphan*/  image ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pt_image*,int,int) ; 
 int /*<<< orphan*/  pt_image_init (struct pt_image*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptu_null (void*) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result init(void)
{
	struct pt_image image;

	memset(&image, 0xcd, sizeof(image));

	pt_image_init(&image, NULL);
	ptu_null(image.name);
	ptu_null(image.sections);
	ptu_null((void *) (uintptr_t) image.readmem.callback);
	ptu_null(image.readmem.context);

	return ptu_passed();
}