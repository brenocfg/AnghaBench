#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct ISO_ARCHIMEDES {int ro_attr; int /*<<< orphan*/  cdfs_attr; int /*<<< orphan*/  execaddr; int /*<<< orphan*/  loadaddr; int /*<<< orphan*/  magic; } ;
struct TYPE_9__ {int su_tail_size; int /*<<< orphan*/ * su_tail_data; TYPE_3__* node; } ;
typedef  TYPE_4__ cd9660node ;
struct TYPE_8__ {char* name; TYPE_2__* inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  st_mtime; } ;
struct TYPE_7__ {TYPE_1__ st; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDFS_PLING ; 
 int RO_ACCESS_OR ; 
 int RO_ACCESS_UR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cd9660_731 (int,int /*<<< orphan*/ ) ; 
 struct ISO_ARCHIMEDES* ecalloc (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int riscos_date (int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
archimedes_convert_node(cd9660node *node)
{
	struct ISO_ARCHIMEDES *arc;
	size_t len;
	int type = -1;
	uint64_t stamp;

	if (node->su_tail_data != NULL)
		/* Something else already has the tail. */
		return;

	len = strlen(node->node->name);
	if (len < 1) return;

	if (len >= 4 && node->node->name[len-4] == ',')
		/* XXX should support ,xxx and ,lxa */
		type = strtoul(node->node->name + len - 3, NULL, 16);
	if (type == -1 && node->node->name[0] != '!')
		return;
	if (type == -1) type = 0;

	assert(sizeof(*arc) == 32);
	arc = ecalloc(1, sizeof(*arc));

	stamp = riscos_date(node->node->inode->st.st_mtime);

	memcpy(arc->magic, "ARCHIMEDES", 10);
	cd9660_731(0xfff00000 | (type << 8) | (stamp >> 32), arc->loadaddr);
	cd9660_731(stamp & 0x00ffffffffULL, arc->execaddr);
	arc->ro_attr = RO_ACCESS_UR | RO_ACCESS_OR;
	arc->cdfs_attr = node->node->name[0] == '!' ? CDFS_PLING : 0;
	node->su_tail_data = (void *)arc;
	node->su_tail_size = sizeof(*arc);
}