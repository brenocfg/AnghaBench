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
struct diffline {struct diffline* right; struct diffline* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct diffline*) ; 

__attribute__((used)) static void
freediff(struct diffline *diffp)
{

	free(diffp->left);
	free(diffp->right);
	free(diffp);
}