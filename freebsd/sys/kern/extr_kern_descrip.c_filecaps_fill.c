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
struct filecaps {int fc_nioctls; int /*<<< orphan*/  fc_fcntls; int /*<<< orphan*/ * fc_ioctls; int /*<<< orphan*/  fc_rights; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_ALL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CAP_FCNTL_ALL ; 

__attribute__((used)) static void
filecaps_fill(struct filecaps *fcaps)
{

	CAP_ALL(&fcaps->fc_rights);
	fcaps->fc_ioctls = NULL;
	fcaps->fc_nioctls = -1;
	fcaps->fc_fcntls = CAP_FCNTL_ALL;
}