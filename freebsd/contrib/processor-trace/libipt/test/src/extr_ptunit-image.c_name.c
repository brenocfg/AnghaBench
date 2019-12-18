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
struct image_fixture {int /*<<< orphan*/  image; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt_image_init (int /*<<< orphan*/ *,char*) ; 
 char* pt_image_name (int /*<<< orphan*/ *) ; 
 struct ptunit_result ptu_passed () ; 
 int /*<<< orphan*/  ptu_str_eq (char const*,char*) ; 

__attribute__((used)) static struct ptunit_result name(struct image_fixture *ifix)
{
	const char *name;

	pt_image_init(&ifix->image, "image-name");

	name = pt_image_name(&ifix->image);
	ptu_str_eq(name, "image-name");

	return ptu_passed();
}