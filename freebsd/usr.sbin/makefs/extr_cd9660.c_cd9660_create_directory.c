#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  iso9660_disk ;
struct TYPE_10__ {int type; TYPE_1__* node; } ;
typedef  TYPE_2__ cd9660node ;
struct TYPE_9__ {int /*<<< orphan*/ * inode; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int CD9660_TYPE_DIR ; 
 int CD9660_TYPE_VIRTUAL ; 
 int /*<<< orphan*/  S_IFDIR ; 
 TYPE_2__* cd9660_create_virtual_entry (int /*<<< orphan*/ *,char const*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cd9660_translate_node_common (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * ecalloc (int,int) ; 

__attribute__((used)) static cd9660node *
cd9660_create_directory(iso9660_disk *diskStructure, const char *name,
    cd9660node *parent, cd9660node *me)
{
	cd9660node *temp;

	temp = cd9660_create_virtual_entry(diskStructure, name, parent, 0, 1);
	if (temp == NULL)
		return NULL;
	temp->node->type |= S_IFDIR;

	temp->type = CD9660_TYPE_DIR | CD9660_TYPE_VIRTUAL;

	temp->node->inode = ecalloc(1, sizeof(*temp->node->inode));
	*temp->node->inode = *me->node->inode;

	if (cd9660_translate_node_common(diskStructure, temp) == 0)
		return NULL;
	return temp;
}