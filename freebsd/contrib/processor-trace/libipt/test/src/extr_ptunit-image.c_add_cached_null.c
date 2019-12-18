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
struct pt_image_section_cache {int dummy; } ;
struct pt_image {int dummy; } ;

/* Variables and functions */
 int pt_image_add_cached (struct pt_image*,struct pt_image_section_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_invalid ; 
 int /*<<< orphan*/  ptu_int_eq (int,int /*<<< orphan*/ ) ; 
 struct ptunit_result ptu_passed () ; 

__attribute__((used)) static struct ptunit_result add_cached_null(void)
{
	struct pt_image_section_cache iscache;
	struct pt_image image;
	int status;

	status = pt_image_add_cached(NULL, &iscache, 0, NULL);
	ptu_int_eq(status, -pte_invalid);

	status = pt_image_add_cached(&image, NULL, 0, NULL);
	ptu_int_eq(status, -pte_invalid);

	return ptu_passed();
}