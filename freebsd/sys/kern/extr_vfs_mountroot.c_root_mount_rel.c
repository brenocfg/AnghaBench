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
struct root_hold_token {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct root_hold_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  TSRELEASE (char*) ; 
 int /*<<< orphan*/  free (struct root_hold_token*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_holds ; 
 int /*<<< orphan*/  root_holds_mtx ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
root_mount_rel(struct root_hold_token *h)
{

	if (h == NULL)
		return;

	mtx_lock(&root_holds_mtx);
	LIST_REMOVE(h, list);
	TSRELEASE("root mount");
	wakeup(&root_holds);
	mtx_unlock(&root_holds_mtx);
	free(h, M_DEVBUF);
}