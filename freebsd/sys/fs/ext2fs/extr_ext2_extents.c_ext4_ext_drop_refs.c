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
struct ext4_extent_path {int ep_depth; int /*<<< orphan*/ * ep_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EXT2EXTENTS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ext4_ext_drop_refs(struct ext4_extent_path *path)
{
	int depth, i;

	if (!path)
		return;

	depth = path->ep_depth;
	for (i = 0; i <= depth; i++, path++)
		if (path->ep_data) {
			free(path->ep_data, M_EXT2EXTENTS);
			path->ep_data = NULL;
		}
}