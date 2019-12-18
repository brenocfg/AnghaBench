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
struct vfs_state {scalar_t__ vs_mp; scalar_t__ vs_vp; scalar_t__ vs_vnlocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfs_rel (scalar_t__) ; 
 int /*<<< orphan*/  vput (scalar_t__) ; 
 int /*<<< orphan*/  vrele (scalar_t__) ; 

__attribute__((used)) static void
nlm_release_vfs_state(struct vfs_state *vs)
{

	if (vs->vs_vp) {
		if (vs->vs_vnlocked)
			vput(vs->vs_vp);
		else
			vrele(vs->vs_vp);
	}
	if (vs->vs_mp)
		vfs_rel(vs->vs_mp);
}