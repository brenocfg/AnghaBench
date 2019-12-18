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
struct pt_image {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_image_fini (struct pt_image*) ; 
 int /*<<< orphan*/  pt_image_init (struct pt_image*,int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result fini_empty(void)
{
	struct pt_image image;

	pt_image_init(&image, NULL);
	pt_image_fini(&image);

	return ptu_passed();
}