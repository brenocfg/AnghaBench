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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  enum symfollow { ____Placeholder_symfollow } symfollow ;

/* Variables and functions */
 int lookupnameat (char*,int,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int
lookupname(char *dirname, enum uio_seg seg, enum symfollow follow,
    vnode_t **dirvpp, vnode_t **compvpp)
{

	return (lookupnameat(dirname, seg, follow, dirvpp, compvpp, NULL));
}