#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct vop_bmap_args {int* a_bnp; int a_bn; int* a_runp; scalar_t__* a_runb; int /*<<< orphan*/ ** a_bop; int /*<<< orphan*/  a_vp; } ;
struct udf_node {TYPE_2__* udfmp; } ;
typedef  int daddr_t ;
struct TYPE_4__ {int bshift; TYPE_1__* im_devvp; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_bufobj; } ;

/* Variables and functions */
 int DEV_BSHIFT ; 
 int EOPNOTSUPP ; 
 int MAXBSIZE ; 
 int UDF_INVALID_BMAP ; 
 struct udf_node* VTON (int /*<<< orphan*/ ) ; 
 int udf_bmap_internal (struct udf_node*,int,int*,int*) ; 

__attribute__((used)) static int
udf_bmap(struct vop_bmap_args *a)
{
	struct udf_node *node;
	uint32_t max_size;
	daddr_t lsector;
	int nblk;
	int error;

	node = VTON(a->a_vp);

	if (a->a_bop != NULL)
		*a->a_bop = &node->udfmp->im_devvp->v_bufobj;
	if (a->a_bnp == NULL)
		return (0);
	if (a->a_runb)
		*a->a_runb = 0;

	/*
	 * UDF_INVALID_BMAP means data embedded into fentry, this is an internal
	 * error that should not be propagated to calling code.
	 * Most obvious mapping for this error is EOPNOTSUPP as we can not truly
	 * translate block numbers in this case.
	 * Incidentally, this return code will make vnode pager to use VOP_READ
	 * to get data for mmap-ed pages and udf_read knows how to do the right
	 * thing for this kind of files.
	 */
	error = udf_bmap_internal(node, a->a_bn << node->udfmp->bshift,
	    &lsector, &max_size);
	if (error == UDF_INVALID_BMAP)
		return (EOPNOTSUPP);
	if (error)
		return (error);

	/* Translate logical to physical sector number */
	*a->a_bnp = lsector << (node->udfmp->bshift - DEV_BSHIFT);

	/*
	 * Determine maximum number of readahead blocks following the
	 * requested block.
	 */
	if (a->a_runp) {
		nblk = (max_size >> node->udfmp->bshift) - 1;
		if (nblk <= 0)
			*a->a_runp = 0;
		else if (nblk >= (MAXBSIZE >> node->udfmp->bshift))
			*a->a_runp = (MAXBSIZE >> node->udfmp->bshift) - 1;
		else
			*a->a_runp = nblk;
	}

	if (a->a_runb) {
		*a->a_runb = 0;
	}

	return (0);
}