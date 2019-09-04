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
struct image {size_t nr; TYPE_1__* line; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static void remove_last_line(struct image *img)
{
	img->len -= img->line[--img->nr].len;
}