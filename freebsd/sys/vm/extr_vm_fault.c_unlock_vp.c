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
struct faultstate {int /*<<< orphan*/ * vp; } ;

/* Variables and functions */
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unlock_vp(struct faultstate *fs)
{

	if (fs->vp != NULL) {
		vput(fs->vp);
		fs->vp = NULL;
	}
}