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
struct cdev {int /*<<< orphan*/  si_children; int /*<<< orphan*/  si_flags; struct cdev* si_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct cdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_CHILD ; 
 int /*<<< orphan*/  si_siblings ; 

__attribute__((used)) static void
dev_dependsl(struct cdev *pdev, struct cdev *cdev)
{

	cdev->si_parent = pdev;
	cdev->si_flags |= SI_CHILD;
	LIST_INSERT_HEAD(&pdev->si_children, cdev, si_siblings);
}