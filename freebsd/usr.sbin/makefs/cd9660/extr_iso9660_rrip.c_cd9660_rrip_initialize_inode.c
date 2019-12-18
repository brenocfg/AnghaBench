#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ISO_SUSP_ATTRIBUTES {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  head; TYPE_4__* node; int /*<<< orphan*/  cn_children; } ;
typedef  TYPE_3__ cd9660node ;
struct TYPE_12__ {TYPE_2__* inode; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_10__ {TYPE_1__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUSP_ENTRY_RRIP_PN ; 
 int /*<<< orphan*/  SUSP_ENTRY_RRIP_PX ; 
 int /*<<< orphan*/  SUSP_ENTRY_RRIP_TF ; 
 int /*<<< orphan*/  SUSP_LOC_ENTRY ; 
 int /*<<< orphan*/  SUSP_TYPE_RRIP ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ISO_SUSP_ATTRIBUTES*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd9660_createSL (TYPE_3__*) ; 
 int /*<<< orphan*/  cd9660node_rrip_pn (struct ISO_SUSP_ATTRIBUTES*,TYPE_4__*) ; 
 int /*<<< orphan*/  cd9660node_rrip_px (struct ISO_SUSP_ATTRIBUTES*,TYPE_4__*) ; 
 int /*<<< orphan*/  cd9660node_rrip_tf (struct ISO_SUSP_ATTRIBUTES*,TYPE_4__*) ; 
 struct ISO_SUSP_ATTRIBUTES* cd9660node_susp_create_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rr_ll ; 

__attribute__((used)) static void
cd9660_rrip_initialize_inode(cd9660node *node)
{
	struct ISO_SUSP_ATTRIBUTES *attr;

	/*
	 * Inode dependent values - this may change,
	 * but for now virtual files and directories do
	 * not have an inode structure
	 */

	if ((node->node != NULL) && (node->node->inode != NULL)) {
		/* PX - POSIX attributes */
		attr = cd9660node_susp_create_node(SUSP_TYPE_RRIP,
			SUSP_ENTRY_RRIP_PX, "PX", SUSP_LOC_ENTRY);
		cd9660node_rrip_px(attr, node->node);

		TAILQ_INSERT_TAIL(&node->head, attr, rr_ll);

		/* TF - timestamp */
		attr = cd9660node_susp_create_node(SUSP_TYPE_RRIP,
			SUSP_ENTRY_RRIP_TF, "TF", SUSP_LOC_ENTRY);
		cd9660node_rrip_tf(attr, node->node);
		TAILQ_INSERT_TAIL(&node->head, attr, rr_ll);

		/* SL - Symbolic link */
		/* ?????????? Dan - why is this here? */
		if (TAILQ_EMPTY(&node->cn_children) &&
		    node->node->inode != NULL &&
		    S_ISLNK(node->node->inode->st.st_mode))
			cd9660_createSL(node);

		/* PN - device number */
		if (node->node->inode != NULL &&
		    ((S_ISCHR(node->node->inode->st.st_mode) ||
		     S_ISBLK(node->node->inode->st.st_mode)))) {
			attr =
			    cd9660node_susp_create_node(SUSP_TYPE_RRIP,
				SUSP_ENTRY_RRIP_PN, "PN",
				SUSP_LOC_ENTRY);
			cd9660node_rrip_pn(attr, node->node);
			TAILQ_INSERT_TAIL(&node->head, attr, rr_ll);
		}
	}
}