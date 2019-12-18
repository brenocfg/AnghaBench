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
struct m_ext2fs {int /*<<< orphan*/  e2fs_bsize; } ;
struct inode {int /*<<< orphan*/  i_facl; int /*<<< orphan*/  i_devvp; struct m_ext2fs* i_e2fs; } ;
struct ext2fs_extattr_header {scalar_t__ h_magic; int h_blocks; } ;
struct ext2fs_extattr_entry {int e_name_len; int /*<<< orphan*/  e_name; int /*<<< orphan*/  e_name_index; } ;
struct buf {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 struct ext2fs_extattr_entry* EXT2_FIRST_ENTRY (struct buf*) ; 
 struct ext2fs_extattr_header* EXT2_HDR (struct buf*) ; 
 int /*<<< orphan*/  EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 
 scalar_t__ EXTATTR_MAGIC ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int ext2_extattr_attrnamespace_to_bsd (int /*<<< orphan*/ ) ; 
 int ext2_extattr_block_check (struct inode*,struct buf*) ; 
 char* ext2_extattr_name_to_bsd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int uiomove (char*,int,struct uio*) ; 

int
ext2_extattr_block_list(struct inode *ip, int attrnamespace,
    struct uio *uio, size_t *size)
{
	struct m_ext2fs *fs;
	struct buf *bp;
	struct ext2fs_extattr_header *header;
	struct ext2fs_extattr_entry *entry;
	const char *attr_name;
	int name_len;
	int error;

	fs = ip->i_e2fs;

	error = bread(ip->i_devvp, fsbtodb(fs, ip->i_facl),
	    fs->e2fs_bsize, NOCRED, &bp);
	if (error) {
		return (error);
	}

	/* Check attributes magic value */
	header = EXT2_HDR(bp);
	if (header->h_magic != EXTATTR_MAGIC || header->h_blocks != 1) {
		brelse(bp);
		return (EINVAL);
	}

	error = ext2_extattr_block_check(ip, bp);
	if (error) {
		brelse(bp);
		return (error);
	}

	for (entry = EXT2_FIRST_ENTRY(bp); !EXT2_IS_LAST_ENTRY(entry);
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