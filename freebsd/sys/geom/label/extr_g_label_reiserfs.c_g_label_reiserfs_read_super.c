#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct g_consumer {TYPE_1__* provider; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_magic; } ;
typedef  TYPE_2__ reiserfs_sb_t ;
typedef  int off_t ;
struct TYPE_5__ {int sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  REISERFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  g_free (TYPE_2__*) ; 
 scalar_t__ g_read_data (struct g_consumer*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static reiserfs_sb_t *
g_label_reiserfs_read_super(struct g_consumer *cp, off_t offset)
{
	reiserfs_sb_t *fs;
	u_int secsize;

	secsize = cp->provider->sectorsize;

	if ((offset % secsize) != 0)
		return (NULL);

	fs = (reiserfs_sb_t *)g_read_data(cp, offset, secsize, NULL);
	if (fs == NULL)
		return (NULL);

	if (strncmp(fs->s_magic, REISERFS_SUPER_MAGIC,
	    strlen(REISERFS_SUPER_MAGIC)) != 0) {
		g_free(fs);
		return (NULL);
	}

	return (fs);
}