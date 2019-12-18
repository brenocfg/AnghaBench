#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_provider {int sectorsize; int /*<<< orphan*/  name; } ;
struct g_consumer {struct g_provider* provider; } ;
struct TYPE_3__ {scalar_t__ s_magic; scalar_t__ s_rev_level; char* s_volume_name; } ;
typedef  TYPE_1__ e2sb_t ;

/* Variables and functions */
 int EXT2FS_SB_OFFSET ; 
 scalar_t__ EXT2_DYNAMIC_REV ; 
 scalar_t__ EXT2_SUPER_MAGIC ; 
 int /*<<< orphan*/  G_LABEL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 scalar_t__ g_read_data (struct g_consumer*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
g_label_ext2fs_taste(struct g_consumer *cp, char *label, size_t size)
{
	struct g_provider *pp;
	e2sb_t *fs;
	char *s_volume_name;

	g_topology_assert_not();
	pp = cp->provider;
	label[0] = '\0';

	if ((EXT2FS_SB_OFFSET % pp->sectorsize) != 0)
		return;

	fs = (e2sb_t *)g_read_data(cp, EXT2FS_SB_OFFSET, pp->sectorsize, NULL);
	if (fs == NULL)
		return;

	/* Check for magic and versio n*/
	if (fs->s_magic == EXT2_SUPER_MAGIC &&
	    fs->s_rev_level == EXT2_DYNAMIC_REV) {
		G_LABEL_DEBUG(1, "ext2fs file system detected on %s.",
		    pp->name);
	} else {
		goto exit_free;
	}

	s_volume_name = fs->s_volume_name;
	/* Terminate label */
	s_volume_name[sizeof(fs->s_volume_name) - 1] = '\0';

	if (s_volume_name[0] == '/')
		s_volume_name += 1;

	/* Check for volume label */
	if (s_volume_name[0] == '\0')
		goto exit_free;

	strlcpy(label, s_volume_name, size);

exit_free:
	g_free(fs);
}