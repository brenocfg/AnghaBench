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
struct ucred {struct label* cr_label; } ;
struct label {int dummy; } ;
struct image_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_CHECK (struct label*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_CRED ; 
 int /*<<< orphan*/  MAGIC_VNODE ; 
 int /*<<< orphan*/  vnode_execve_will_transition ; 

__attribute__((used)) static int
test_vnode_execve_will_transition(struct ucred *old, struct vnode *vp,
    struct label *filelabel, struct label *interpvplabel,
    struct image_params *imgp, struct label *execlabel)
{

	LABEL_CHECK(old->cr_label, MAGIC_CRED);
	LABEL_CHECK(filelabel, MAGIC_VNODE);
	LABEL_CHECK(interpvplabel, MAGIC_VNODE);
	LABEL_CHECK(execlabel, MAGIC_CRED);
	COUNTER_INC(vnode_execve_will_transition);

	return (0);
}