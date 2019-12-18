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
struct ldm_xvblk {struct ldm_xvblk* data; } ;
struct ldm_vblk {struct ldm_vblk* data; } ;
struct ldm_db {int /*<<< orphan*/  vblks; int /*<<< orphan*/  xvblks; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct ldm_xvblk* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct ldm_xvblk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  g_free (struct ldm_xvblk*) ; 

__attribute__((used)) static void
ldm_vmdb_free(struct ldm_db *db)
{
	struct ldm_vblk *vblk;
	struct ldm_xvblk *xvblk;

	while (!LIST_EMPTY(&db->xvblks)) {
		xvblk = LIST_FIRST(&db->xvblks);
		LIST_REMOVE(xvblk, entry);
		g_free(xvblk->data);
		g_free(xvblk);
	}
	while (!LIST_EMPTY(&db->vblks)) {
		vblk = LIST_FIRST(&db->vblks);
		LIST_REMOVE(vblk, entry);
		g_free(vblk);
	}
}