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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  long u_int ;
typedef  int u_char ;
struct ufs2_dinode {scalar_t__ di_extsize; int /*<<< orphan*/ * di_extb; } ;
struct inodesc {scalar_t__ id_number; } ;
struct TYPE_3__ {scalar_t__ b_buf; } ;
struct bufarea {TYPE_1__ b_un; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_4__ {long fs_fsize; long fs_bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_EXTATTR ; 
 int DIRBLKSIZ ; 
 int STOP ; 
 struct bufarea* getdatablk (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__ sblock ; 

int
eascan(struct inodesc *idesc, struct ufs2_dinode *dp)
{
#if 1
	return (0);
#else
	struct bufarea *bp;
	u_int dsize, n;
	u_char *cp;
	long blksiz;
	char dbuf[DIRBLKSIZ];

	printf("Inode %ju extsize %ju\n",
	   (intmax_t)idesc->id_number, (uintmax_t)dp->di_extsize);
	if (dp->di_extsize == 0)
		return 0;
	if (dp->di_extsize <= sblock.fs_fsize)
		blksiz = sblock.fs_fsize;
	else
		blksiz = sblock.fs_bsize;
	printf("blksiz = %ju\n", (intmax_t)blksiz);
	bp = getdatablk(dp->di_extb[0], blksiz, BT_EXTATTR);
	cp = (u_char *)bp->b_un.b_buf;
	for (n = 0; n < blksiz; n++) {
		printf("%02x", cp[n]);
		if ((n & 31) == 31)
			printf("\n");
	}
	return (STOP);
#endif
}