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
struct image {int /*<<< orphan*/  line_allocated; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct image*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_image(struct image *image)
{
	free(image->buf);
	free(image->line_allocated);
	memset(image, 0, sizeof(*image));
}