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
struct vop_open_args {int /*<<< orphan*/  a_td; int /*<<< orphan*/  a_vp; } ;
struct udf_node {TYPE_1__* fentry; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  inf_len; } ;

/* Variables and functions */
 struct udf_node* VTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_create_vobject (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udf_open(struct vop_open_args *ap) {
	struct udf_node *np = VTON(ap->a_vp);
	off_t fsize;

	fsize = le64toh(np->fentry->inf_len);
	vnode_create_vobject(ap->a_vp, fsize, ap->a_td);
	return 0;
}