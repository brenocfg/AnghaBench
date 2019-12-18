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
struct knote {int dummy; } ;
struct file {int /*<<< orphan*/  f_vnode; } ;

/* Variables and functions */
 int VOP_KQFILTER (int /*<<< orphan*/ ,struct knote*) ; 

__attribute__((used)) static int
vn_kqfilter(struct file *fp, struct knote *kn)
{

	return (VOP_KQFILTER(fp->f_vnode, kn));
}