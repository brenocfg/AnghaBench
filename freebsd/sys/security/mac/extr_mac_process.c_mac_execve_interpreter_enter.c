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
struct vnode {int /*<<< orphan*/  v_label; } ;
struct label {int dummy; } ;

/* Variables and functions */
 int MPC_OBJECT_VNODE ; 
 int mac_labeled ; 
 int /*<<< orphan*/  mac_vnode_copy_label (int /*<<< orphan*/ ,struct label*) ; 
 struct label* mac_vnode_label_alloc () ; 

void
mac_execve_interpreter_enter(struct vnode *interpvp,
    struct label **interpvplabel)
{

	if (mac_labeled & MPC_OBJECT_VNODE) {
		*interpvplabel = mac_vnode_label_alloc();
		mac_vnode_copy_label(interpvp->v_label, *interpvplabel);
	} else
		*interpvplabel = NULL;
}