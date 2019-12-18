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
struct pt_image {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dupstr (char const*) ; 
 int /*<<< orphan*/  memset (struct pt_image*,int /*<<< orphan*/ ,int) ; 

void pt_image_init(struct pt_image *image, const char *name)
{
	if (!image)
		return;

	memset(image, 0, sizeof(*image));

	image->name = dupstr(name);
}