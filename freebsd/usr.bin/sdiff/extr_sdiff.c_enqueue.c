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
struct diffline {char* left; char div; char* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct diffline*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diffentries ; 
 int /*<<< orphan*/  diffhead ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct diffline* malloc (int) ; 

__attribute__((used)) static void
enqueue(char *left, char divider, char *right)
{
	struct diffline *diffp;

	if (!(diffp = malloc(sizeof(struct diffline))))
		err(2, "enqueue");
	diffp->left = left;
	diffp->div = divider;
	diffp->right = right;
	STAILQ_INSERT_TAIL(&diffhead, diffp, diffentries);
}