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
struct uio {int dummy; } ;
struct m_ext2fs {scalar_t__ e2fs_bsize; } ;
struct inode {int /*<<< orphan*/  i_number; int /*<<< orphan*/  i_devvp; struct m_ext2fs* i_e2fs; } ;
struct ext2fs_extattr_entry {int e_name_len; int /*<<< orphan*/  e_name; int /*<<< orphan*/  e_name_index; } ;
struct ext2fs_extattr_dinode_header {scalar_t__ h_magic; } ;
struct ext2fs_dinode {int e2di_extra_isize; } ;
struct buf {scalar_t__ b_data; } ;

/* Variables and functions */
 int E2FS_REV0_INODE_SIZE ; 
 int ENOTSUP ; 
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 struct ext2fs_extattr_entry* EXT2_IFIRST (struct ext2fs_extattr_dinode_header*) ; 
 int EXT2_INODE_SIZE (struct m_ext2fs*) ; 
 int /*<<< orphan*/  EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 
 scalar_t__ EXTATTR_MAGIC ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int ext2_extattr_attrnamespace_to_bsd (int /*<<< orphan*/ ) ; 
 int ext2_extattr_check (struct ext2fs_extattr_entry*,char*) ; 
 char* ext2_extattr_name_to_bsd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_to_fsba (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int ino_to_fsbo (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int uiomove (char*,int,struct uio*) ; 

int
ext2_extattr_inode_list(struct inode *ip, int attrnamespace,
    struct uio *uio, size_t *size)
{
	struct m_ext2fs *fs;
	struct buf *bp;
	struct ext2fs_extattr_dinode_header *header;
	struct ext2fs_extattr_entry *entry;
	const char *attr_name;
	int name_len;
	int error;

	fs = ip->i_e2fs;

	if ((error = bread(ip->i_devvp,
	    fsbtodb(fs, ino_to_fsba(fs, ip->i_number)),
	    (int)fs->e2fs_bsize, NOCRED, &bp)) != 0) {
		brelse(bp);
		return (error);
	}

	struct ext2fs_dinode *dinode = (struct ext2fs_dinode *)
	    ((char *)bp->b_data +
	    EXT2_INODE_SIZE(fs) * ino_to_fsbo(fs, ip->i_number));

	/* Check attributes magic value */
	header = (struct ext2fs_extattr_dinode_header *)((char *)dinode +
	    E2FS_REV0_INODE_SIZE + dinode->e2di_extra_isize);

	if (header->h_magic != EXTATTR_MAGIC) {
		brelse(bp);
		return (0);
	}

	error = ext2_extattr_check(EXT2_IFIRST(header),
	    (char *)dinode + EXT2_INODE_SIZE(fs));
	if (error) {
		brelse(bp);
		return (error);
	}

	for (entry = EXT2_IFIRST(header); !EXT2_IS_LAST_ENTRY(entry);
	    entry = EXT2_EXTATTR_NEXT(entry)) {
		if (ext2_extattr_attrnamespace_to_bsd(entry->e_name_index) !=
		    attrnamespace)
			continue;

		name_len = entry->e_name_len;
		attr_name = ext2_extattr_name_to_bsd(entry->e_name_index,
		    entry->e_name, &name_len);
		if (!attr_name) {
			brelse(bp);
			return (ENOTSUP);
		}

		if (size != NULL)
			*size += name_len + 1;

		if (uio != NULL) {
			char *name = malloc(name_len + 1, M_TEMP, M_WAITOK);
			name[0] = name_len;
			memcpy(&name[1], attr_name, name_len);
			error = uiomove(name, name_len + 1, uio);
			free(name, M_TEMP);
			if (error)
				break;
		}
	}

	brelse(bp);

	return (error);
}