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
struct bsdtar {int return_value; int /*<<< orphan*/  matching; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_archive (struct bsdtar*,char,int /*<<< orphan*/ *) ; 
 scalar_t__ unmatched_inclusions_warn (int /*<<< orphan*/ ,char*) ; 

void
tar_mode_t(struct bsdtar *bsdtar)
{
	read_archive(bsdtar, 't', NULL);
	if (unmatched_inclusions_warn(bsdtar->matching,
	    "Not found in archive") != 0)
		bsdtar->return_value = 1;
}