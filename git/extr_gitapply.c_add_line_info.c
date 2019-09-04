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
struct image {int nr; TYPE_1__* line_allocated; int /*<<< orphan*/  alloc; } ;
struct TYPE_2__ {size_t len; unsigned int flag; int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_line (char const*,size_t) ; 

__attribute__((used)) static void add_line_info(struct image *img, const char *bol, size_t len, unsigned flag)
{
	ALLOC_GROW(img->line_allocated, img->nr + 1, img->alloc);
	img->line_allocated[img->nr].len = len;
	img->line_allocated[img->nr].hash = hash_line(bol, len);
	img->line_allocated[img->nr].flag = flag;
	img->nr++;
}