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
struct pt_image {int /*<<< orphan*/  name; int /*<<< orphan*/  sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pt_image*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pt_section_list_free_tail (int /*<<< orphan*/ ) ; 

void pt_image_fini(struct pt_image *image)
{
	if (!image)
		return;

	pt_section_list_free_tail(image->sections);
	free(image->name);

	memset(image, 0, sizeof(*image));
}