#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_provider {int /*<<< orphan*/  name; } ;
struct g_consumer {struct g_provider* provider; } ;
struct TYPE_4__ {int s_version; char* s_volume_name; } ;
typedef  TYPE_1__ reiserfs_sb_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_LABEL_DEBUG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REISERFS_NEW_DISK_OFFSET ; 
 int /*<<< orphan*/  REISERFS_OLD_DISK_OFFSET ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 TYPE_1__* g_label_reiserfs_read_super (struct g_consumer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void
g_label_reiserfs_taste(struct g_consumer *cp, char *label, size_t size)
{
	struct g_provider *pp;
	reiserfs_sb_t *fs;

	g_topology_assert_not();
	pp = cp->provider;
	label[0] = '\0';

	/* Try old format */
	fs = g_label_reiserfs_read_super(cp, REISERFS_OLD_DISK_OFFSET);
	if (fs == NULL) {
		/* Try new format */
		fs = g_label_reiserfs_read_super(cp, REISERFS_NEW_DISK_OFFSET);
	}
	if (fs == NULL)
		return;

	/* Check version */
	if (fs->s_version == 2) {
		G_LABEL_DEBUG(1, "reiserfs file system detected on %s.",
		    pp->name);
	} else {
		goto exit_free;
	}

	/* Check for volume label */
	if (fs->s_volume_name[0] == '\0')
		goto exit_free;

	/* Terminate label */
	fs->s_volume_name[sizeof(fs->s_volume_name) - 1] = '\0';
	strlcpy(label, fs->s_volume_name, size);

exit_free:
	g_free(fs);
}