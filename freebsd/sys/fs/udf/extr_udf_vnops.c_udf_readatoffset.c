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
struct vnode {int dummy; } ;
struct udf_node {struct file_entry* fentry; struct vnode* i_vnode; struct udf_mnt* udfmp; } ;
struct udf_mnt {int bmask; } ;
struct file_entry {int /*<<< orphan*/  l_ad; int /*<<< orphan*/  l_ea; int /*<<< orphan*/ * data; } ;
struct buf {int /*<<< orphan*/ * b_data; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  daddr_t ;

/* Variables and functions */
 scalar_t__ MAXBSIZE ; 
 int /*<<< orphan*/  NOCRED ; 
 int UDF_INVALID_BMAP ; 
 int blkoff (struct udf_mnt*,int) ; 
 int bread (struct vnode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  lblkno (struct udf_mnt*,int) ; 
 size_t le32toh (int /*<<< orphan*/ ) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int udf_bmap_internal (struct udf_node*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
udf_readatoffset(struct udf_node *node, int *size, off_t offset,
    struct buf **bp, uint8_t **data)
{
	struct udf_mnt *udfmp = node->udfmp;
	struct vnode *vp = node->i_vnode;
	struct file_entry *fentry;
	struct buf *bp1;
	uint32_t max_size;
	daddr_t sector;
	off_t off;
	int adj_size;
	int error;

	/*
	 * This call is made *not* only to detect UDF_INVALID_BMAP case,
	 * max_size is used as an ad-hoc read-ahead hint for "normal" case.
	 */
	error = udf_bmap_internal(node, offset, &sector, &max_size);
	if (error == UDF_INVALID_BMAP) {
		/*
		 * This error means that the file *data* is stored in the
		 * allocation descriptor field of the file entry.
		 */
		fentry = node->fentry;
		*data = &fentry->data[le32toh(fentry->l_ea)];
		*size = le32toh(fentry->l_ad);
		if (offset >= *size)
			*size = 0;
		else {
			*data += offset;
			*size -= offset;
		}
		return (0);
	} else if (error != 0) {
		return (error);
	}

	/* Adjust the size so that it is within range */
	if (*size == 0 || *size > max_size)
		*size = max_size;

	/*
	 * Because we will read starting at block boundary, we need to adjust
	 * how much we need to read so that all promised data is in.
	 * Also, we can't promise to read more than MAXBSIZE bytes starting
	 * from block boundary, so adjust what we promise too.
	 */
	off = blkoff(udfmp, offset);
	*size = min(*size, MAXBSIZE - off);
	adj_size = (*size + off + udfmp->bmask) & ~udfmp->bmask;
	*bp = NULL;
	if ((error = bread(vp, lblkno(udfmp, offset), adj_size, NOCRED, bp))) {
		printf("warning: udf_readlblks returned error %d\n", error);
		/* note: *bp may be non-NULL */
		return (error);
	}

	bp1 = *bp;
	*data = (uint8_t *)&bp1->b_data[offset & udfmp->bmask];
	return (0);
}