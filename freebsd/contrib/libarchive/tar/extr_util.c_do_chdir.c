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
struct bsdtar {int /*<<< orphan*/ * pending_chdir; } ;

/* Variables and functions */
 scalar_t__ chdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lafe_errc (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
do_chdir(struct bsdtar *bsdtar)
{
	if (bsdtar->pending_chdir == NULL)
		return;

	if (chdir(bsdtar->pending_chdir) != 0) {
		lafe_errc(1, 0, "could not chdir to '%s'\n",
		    bsdtar->pending_chdir);
	}
	free(bsdtar->pending_chdir);
	bsdtar->pending_chdir = NULL;
}