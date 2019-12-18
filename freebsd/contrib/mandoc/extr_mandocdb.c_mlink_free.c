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
struct mlink {struct mlink* fsec; struct mlink* name; struct mlink* arch; struct mlink* dsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mlink*) ; 

__attribute__((used)) static void
mlink_free(struct mlink *mlink)
{

	free(mlink->dsec);
	free(mlink->arch);
	free(mlink->name);
	free(mlink->fsec);
	free(mlink);
}