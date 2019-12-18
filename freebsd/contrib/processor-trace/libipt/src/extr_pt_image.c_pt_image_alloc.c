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
struct pt_image {int dummy; } ;

/* Variables and functions */
 struct pt_image* malloc (int) ; 
 int /*<<< orphan*/  pt_image_init (struct pt_image*,char const*) ; 

struct pt_image *pt_image_alloc(const char *name)
{
	struct pt_image *image;

	image = malloc(sizeof(*image));
	if (image)
		pt_image_init(image, name);

	return image;
}