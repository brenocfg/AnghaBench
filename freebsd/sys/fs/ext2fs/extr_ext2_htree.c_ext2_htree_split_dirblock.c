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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct m_ext2fs {int dummy; } ;
struct inode {struct m_ext2fs* i_e2fs; } ;
struct ext2fs_htree_sort_entry {int h_size; int h_offset; int h_hash; } ;
struct ext2fs_direct_tail {int dummy; } ;
struct ext2fs_direct_2 {int e2d_reclen; scalar_t__ e2d_namlen; scalar_t__ e2d_ino; int /*<<< orphan*/  e2d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_ROCOMPAT_METADATA_CKSUM ; 
 int /*<<< orphan*/  EXT2_DIRENT_TAIL (char*,int) ; 
 int EXT2_DIR_REC_LEN (scalar_t__) ; 
 scalar_t__ EXT2_HAS_RO_COMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_append_entry (char*,int,struct ext2fs_direct_2*,struct ext2fs_direct_2*,int) ; 
 int /*<<< orphan*/  ext2_htree_cmp_sort_entry ; 
 int /*<<< orphan*/  ext2_htree_hash (int /*<<< orphan*/ ,scalar_t__,int*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext2_init_dirent_tail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  qsort (struct ext2fs_htree_sort_entry*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_htree_split_dirblock(struct inode *ip, char *block1, char *block2,
    uint32_t blksize, uint32_t *hash_seed, uint8_t hash_version,
    uint32_t *split_hash, struct ext2fs_direct_2 *entry)
{
	struct m_ext2fs *fs;
	int entry_cnt = 0;
	int size = 0, csum_size = 0;
	int i, k;
	uint32_t offset;
	uint16_t entry_len = 0;
	uint32_t entry_hash;
	struct ext2fs_direct_2 *ep, *last;
	char *dest;
	struct ext2fs_htree_sort_entry *sort_info;

	fs = ip->i_e2fs;
	ep = (struct ext2fs_direct_2 *)block1;
	dest = block2;
	sort_info = (struct ext2fs_htree_sort_entry *)
	    ((char *)block2 + blksize);

	if (EXT2_HAS_RO_COMPAT_FEATURE(fs, EXT2F_ROCOMPAT_METADATA_CKSUM))
		csum_size = sizeof(struct ext2fs_direct_tail);

	/*
	 * Calculate name hash value for the entry which is to be added.
	 */
	ext2_htree_hash(entry->e2d_name, entry->e2d_namlen, hash_seed,
	    hash_version, &entry_hash, NULL);

	/*
	 * Fill in directory entry sort descriptors.
	 */
	while ((char *)ep < block1 + blksize - csum_size) {
		if (ep->e2d_ino && ep->e2d_namlen) {
			entry_cnt++;
			sort_info--;
			sort_info->h_size = ep->e2d_reclen;
			sort_info->h_offset = (char *)ep - block1;
			ext2_htree_hash(ep->e2d_name, ep->e2d_namlen,
			    hash_seed, hash_version,
			    &sort_info->h_hash, NULL);
		}
		ep = (struct ext2fs_direct_2 *)
		    ((char *)ep + ep->e2d_reclen);
	}

	/*
	 * Sort directory entry descriptors by name hash value.
	 */
	qsort(sort_info, entry_cnt, sizeof(struct ext2fs_htree_sort_entry),
	    ext2_htree_cmp_sort_entry);

	/*
	 * Count the number of entries to move to directory block 2.
	 */
	for (i = entry_cnt - 1; i >= 0; i--) {
		if (sort_info[i].h_size + size > blksize / 2)
			break;
		size += sort_info[i].h_size;
	}

	*split_hash = sort_info[i + 1].h_hash;

	/*
	 * Set collision bit.
	 */
	if (*split_hash == sort_info[i].h_hash)
		*split_hash += 1;

	/*
	 * Move half of directory entries from block 1 to block 2.
	 */
	for (k = i + 1; k < entry_cnt; k++) {
		ep = (struct ext2fs_direct_2 *)((char *)block1 +
		    sort_info[k].h_offset);
		entry_len = EXT2_DIR_REC_LEN(ep->e2d_namlen);
		memcpy(dest, ep, entry_len);
		((struct ext2fs_direct_2 *)dest)->e2d_reclen = entry_len;
		/* Mark directory entry as unused. */
		ep->e2d_ino = 0;
		dest += entry_len;
	}
	dest -= entry_len;

	/* Shrink directory entries in block 1. */
	last = (struct ext2fs_direct_2 *)block1;
	entry_len = 0;
	for (offset = 0; offset < blksize - csum_size; ) {
		ep = (struct ext2fs_direct_2 *)(block1 + offset);
		offset += ep->e2d_reclen;
		if (ep->e2d_ino) {
			last = (struct ext2fs_direct_2 *)
			    ((char *)last + entry_len);
			entry_len = EXT2_DIR_REC_LEN(ep->e2d_namlen);
			memcpy((void *)last, (void *)ep, entry_len);
			last->e2d_reclen = entry_len;
		}
	}

	if (entry_hash >= *split_hash) {
		/* Add entry to block 2. */
		ext2_append_entry(block2, blksize,
		    (struct ext2fs_direct_2 *)dest, entry, csum_size);

		/* Adjust length field of last entry of block 1. */
		last->e2d_reclen = block1 + blksize - (char *)last - csum_size;
	} else {
		/* Add entry to block 1. */
		ext2_append_entry(block1, blksize, last, entry, csum_size);

		/* Adjust length field of last entry of block 2. */
		((struct ext2fs_direct_2 *)dest)->e2d_reclen =
		    block2 + blksize - dest - csum_size;
	}

	if (csum_size) {
		ext2_init_dirent_tail(EXT2_DIRENT_TAIL(block1, blksize));
		ext2_init_dirent_tail(EXT2_DIRENT_TAIL(block2, blksize));
	}

	return (0);
}