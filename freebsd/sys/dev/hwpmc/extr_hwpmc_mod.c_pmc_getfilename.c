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
struct vnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  vn_fullpath (int /*<<< orphan*/ ,struct vnode*,char**,char**) ; 

__attribute__((used)) static void
pmc_getfilename(struct vnode *v, char **fullpath, char **freepath)
{

	*fullpath = "unknown";
	*freepath = NULL;
	vn_fullpath(curthread, v, fullpath, freepath);
}