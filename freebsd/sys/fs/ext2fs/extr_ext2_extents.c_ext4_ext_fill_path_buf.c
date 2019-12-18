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
struct ext4_extent_path {int /*<<< orphan*/ * ep_data; } ;
struct buf {int /*<<< orphan*/  b_bufsize; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ext4_ext_fill_path_buf(struct ext4_extent_path *path, struct buf *bp)
{

	KASSERT(path->ep_data != NULL,
	    ("ext4_ext_fill_path_buf: bad ep_data"));

	memcpy(bp->b_data, path->ep_data, bp->b_bufsize);
}