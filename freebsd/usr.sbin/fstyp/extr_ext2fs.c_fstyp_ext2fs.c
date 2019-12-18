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
struct TYPE_3__ {scalar_t__ s_magic; scalar_t__ s_rev_level; char* s_volume_name; } ;
typedef  TYPE_1__ e2sb_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2FS_SB_OFFSET ; 
 scalar_t__ EXT2_DYNAMIC_REV ; 
 scalar_t__ EXT2_SUPER_MAGIC ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

int
fstyp_ext2fs(FILE *fp, char *label, size_t size)
{
	e2sb_t *fs;
	char *s_volume_name;

	fs = (e2sb_t *)read_buf(fp, EXT2FS_SB_OFFSET, 512);
	if (fs == NULL)
		return (1);

	/* Check for magic and versio n*/
	if (fs->s_magic == EXT2_SUPER_MAGIC &&
	    fs->s_rev_level == EXT2_DYNAMIC_REV) {
		//G_LABEL_DEBUG(1, "ext2fs file system detected on %s.",
		//    pp->name);
	} else {
		free(fs);
		return (1);
	}

	s_volume_name = fs->s_volume_name;
	/* Terminate label */
	s_volume_name[sizeof(fs->s_volume_name) - 1] = '\0';

	if (s_volume_name[0] == '/')
		s_volume_name += 1;

	strlcpy(label, s_volume_name, size);
	free(fs);

	return (0);
}