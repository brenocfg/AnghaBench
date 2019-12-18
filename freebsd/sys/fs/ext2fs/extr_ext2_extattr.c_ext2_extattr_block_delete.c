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
struct m_ext2fs {int /*<<< orphan*/  e2fs_bsize; } ;
struct inode {int /*<<< orphan*/  i_vnode; int /*<<< orphan*/  i_facl; int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_devvp; struct m_ext2fs* i_e2fs; } ;
struct ext2fs_extattr_header {scalar_t__ h_magic; int h_blocks; int h_refcount; } ;
struct ext2fs_extattr_entry {int e_name_len; int /*<<< orphan*/  e_name; int /*<<< orphan*/  e_name_index; } ;
struct buf {scalar_t__ b_bufsize; scalar_t__ b_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOATTR ; 
 int ENOTSUP ; 
 struct ext2fs_extattr_entry* EXT2_EXTATTR_NEXT (struct ext2fs_extattr_entry*) ; 
 struct ext2fs_extattr_entry* EXT2_FIRST_ENTRY (struct buf*) ; 
 struct ext2fs_extattr_header* EXT2_HDR (struct buf*) ; 
 scalar_t__ EXT2_IS_LAST_ENTRY (struct ext2fs_extattr_entry*) ; 
 scalar_t__ EXTATTR_MAGIC ; 
 int /*<<< orphan*/  NOCRED ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 scalar_t__ btodb (int /*<<< orphan*/ ) ; 
 int bwrite (struct buf*) ; 
 int /*<<< orphan*/  ext2_blkfree (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext2_extattr_attrnamespace_to_bsd (int /*<<< orphan*/ ) ; 
 int ext2_extattr_block_check (struct inode*,struct buf*) ; 
 int ext2_extattr_block_clone (struct inode*,struct buf**) ; 
 int /*<<< orphan*/  ext2_extattr_delete_entry (scalar_t__,struct ext2fs_extattr_entry*,struct ext2fs_extattr_entry*,scalar_t__) ; 
 char* ext2_extattr_name_to_bsd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ext2_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

int
ext2_extattr_block_delete(struct inode *ip, int attrnamespace, const char *name)
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

	if (header->h_refcount > 1) {
		error = ext2_extattr_block_clone(ip, &bp);
		if (error) {
			brelse(bp);
			return (error);
		}
	}

	/* If I am last entry, clean me and free the block */
	entry = EXT2_FIRST_ENTRY(bp);
	if (EXT2_IS_LAST_ENTRY(EXT2_EXTATTR_NEXT(entry)) &&
	    (ext2_extattr_attrnamespace_to_bsd(entry->e_name_index) ==
	    attrnamespace)) {

		name_len = entry->e_name_len;
		attr_name = ext2_extattr_name_to_bsd(entry->e_name_index,
		    entry->e_name, &name_len);
		if (!attr_name) {
			brelse(bp);
			return (ENOTSUP);
		}

		if (strlen(name) == name_len &&
		    0 == strncmp(attr_name, name, name_len)) {
			ip->i_blocks -= btodb(fs->e2fs_bsize);
			ext2_blkfree(ip, ip->i_facl, fs->e2fs_bsize);
			ip->i_facl = 0;
			error = ext2_update(ip->i_vnode, 1);

			brelse(bp);
			return (error);
		}
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

		if (strlen(name) == name_len &&
		    0 == strncmp(attr_name, name, name_len)) {
			ext2_extattr_delete_entry(bp->b_data,
			    EXT2_FIRST_ENTRY(bp), entry,
			    bp->b_data + bp->b_bufsize);

			return (bwrite(bp));
		}
	}

	brelse(bp);

	return (ENOATTR);
}